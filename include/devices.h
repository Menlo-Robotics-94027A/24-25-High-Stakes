#include "main.h"
#include "lemlib/api.hpp"

// Smart Port Devices
extern pros::MotorGroup left_motors;
extern pros::MotorGroup right_motors;

extern pros::Imu inertial_sensor;
extern pros::Rotation horizontal_rotation_sensor;
extern pros::Rotation vertical_rotation_sensor_1;
extern pros::Rotation vertical_rotation_sensor_2;

extern pros::MotorGroup intake_rollers;
extern pros::MotorGroup intake_belt;

// 3-Wire Devices
extern pros::adi::DigitalOut grabber_piston;
extern pros::adi::DigitalOut elevation_piston;
extern pros::adi::DigitalOut arm;

// Wireless Devices
extern pros::Controller controller;
extern pros::Controller partner_controller;
 
// Drivetrain Configuration
extern lemlib::Drivetrain drivetrain;
 
// PID Tuning
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;
 
// Odometry Configuration
extern lemlib::TrackingWheel horizontal_tracking_wheel;
extern lemlib::TrackingWheel vertical_tracking_wheel_1;
extern lemlib::TrackingWheel vertical_tracking_wheel_2;

extern lemlib::OdomSensors odometry_sensors;
 
// Input Scaling
extern lemlib::ExpoDriveCurve throttle_curve;
extern lemlib::ExpoDriveCurve steering_curve;
 
// LemLib Chassis (Drivetrain + PID + Odometry)
extern lemlib::Chassis chassis;