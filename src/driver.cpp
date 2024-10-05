#include "driver.h"
#include "liblvgl/misc/lv_fs.h"

typedef FILE *pc_file_t;

void* pcfs_open(struct _lv_fs_drv_t *drv, const char *fn, lv_fs_mode_t mode) {
  errno = 0;
  const char *flags = "";
  if (mode == LV_FS_MODE_WR)
    flags = "wb";
  else if (mode == LV_FS_MODE_RD)
    flags = "rb";
  else if (mode == (LV_FS_MODE_WR | LV_FS_MODE_RD))
    flags = "a+";

  char buf[256];
  sprintf(buf, "%s", fn);
  pc_file_t f = fopen(buf, flags);

  if (f == NULL)
    return NULL;
  else {
    fseek(f, 0, SEEK_SET);
    return f;
  }
}

lv_fs_res_t pcfs_close(struct _lv_fs_drv_t *drv, void *file_p) {
  pc_file_t *fp = (pc_file_t *)file_p;
  fclose(*fp);
  return LV_FS_RES_OK;
}

lv_fs_res_t pcfs_read(struct _lv_fs_drv_t *drv, void *file_p, void *buf, uint32_t btr,
                             uint32_t *br) {
  pc_file_t *fp = (pc_file_t *)file_p;
  *br = fread(buf, 1, btr, *fp);
  return LV_FS_RES_OK;
}

lv_fs_res_t pcfs_seek(struct _lv_fs_drv_t *drv, void *file_p, uint32_t pos, lv_fs_whence_t whence) {
  pc_file_t *fp = (pc_file_t *)file_p;
  int origin;
  switch (whence) {
    case LV_FS_SEEK_SET:
      origin = SEEK_SET;
      break;
    case LV_FS_SEEK_CUR:
      origin = SEEK_CUR;
      break;
    case LV_FS_SEEK_END:
      origin = SEEK_END;
      break;
    default:
      return LV_FS_RES_INV_PARAM;
  }
  fseek(*fp, pos, origin);
  return LV_FS_RES_OK;
}

lv_fs_res_t pcfs_tell(struct _lv_fs_drv_t *drv, void *file_p, uint32_t *pos_p) {
  pc_file_t *fp = (pc_file_t *)file_p;
  *pos_p = ftell(*fp);
  return LV_FS_RES_OK;
}

void registerDriver() {
  _lv_fs_init();
  lv_fs_drv_t pcfs_drv;
  lv_fs_drv_init(&pcfs_drv);

  pcfs_drv.cache_size = sizeof(pc_file_t);
  pcfs_drv.letter = 'S';
  pcfs_drv.open_cb = pcfs_open;
  pcfs_drv.close_cb = pcfs_close;
  pcfs_drv.read_cb = pcfs_read;
  pcfs_drv.seek_cb = pcfs_seek;
  pcfs_drv.tell_cb = pcfs_tell;
  lv_fs_drv_register(&pcfs_drv);
}