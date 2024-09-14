#include <stdio.h>
#include "main.h"

typedef FILE * pc_file_t;

lv_fs_res_t pcfs_open(void * file_p, const char * fn, lv_fs_mode_t mode);
lv_fs_res_t pcfs_close(void * file_p);
lv_fs_res_t pcfs_read(void * file_p, void * buf, uint32_t btr, uint32_t * br);
lv_fs_res_t pcfs_seek(void * file_p, uint32_t pos);
lv_fs_res_t pcfs_tell(void * file_p, uint32_t * pos_p);

void registerDriver();