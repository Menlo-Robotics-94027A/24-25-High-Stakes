#include "devices.hpp"

// Smart Port Devices
// 1: Left Motor 1
// 2: Left Motor 2
// 3: Left Motor 3
// 4: *Empty*
// 5: *Empty*
// 6: *Empty*
// 7: Inertial Sensor
// 8: *Empty*
// 9: *Empty*
// 10: *Empty*
// 11: Vertical Rotation Sensor
// 12: Intake Belt
// 13: Intake Rollers
// 14: *Empty*
// 15: *Empty*
// 16: *Empty*
// 17: *Empty*
// 18: Right Motor 1
// 19: Right Motor 2
// 20: Right Motor 3
// 21: *Empty*
pros::MotorGroup left_motors({-1, -2, -3}, pros::MotorGearset::green);
pros::MotorGroup right_motors({18, 19, 20}, pros::MotorGearset::green);

pros::Imu inertial_sensor(7);
pros::Rotation horizontal_rotation_sensor(-8);
pros::Rotation vertical_rotation_sensor(-11);

pros::MotorGroup intake_belt({12}, pros::MotorGearset::blue);
pros::MotorGroup intake_rollers({-13}, pros::MotorGearset::green);

// 3-Wire Devices
// A: Grabber Piston
// B: Elevation Piston
// C: Arm
// D: *Empty*
// E: *Empty*
// F: *Empty*
// G: *Empty*
// H: *Empty*
pros::adi::DigitalOut grabber_piston('A', LOW);
pros::adi::DigitalOut elevation_piston('B', HIGH);
pros::adi::DigitalOut arm('C', LOW);

// Wireless Devices
pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::Controller partner_controller(pros::E_CONTROLLER_PARTNER);

// Drivetrain Configuration
lemlib::Drivetrain drivetrain(&left_motors, &right_motors, 11.75,
                              lemlib::Omniwheel::NEW_275, 360, 2);

// PID Tuning
lemlib::ControllerSettings lateral_controller(12, 0, 5, 3, 1, 100, 3, 500, 0);
lemlib::ControllerSettings angular_controller(3, 0, 10, 3, 1, 100, 3, 500, 0);

// Odometry Configuration
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_rotation_sensor,
                                                lemlib::Omniwheel::NEW_275, 7);
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_rotation_sensor,
                                              lemlib::Omniwheel::NEW_275,
                                              -0.75);

lemlib::OdomSensors odometry_sensors(&vertical_tracking_wheel, nullptr,
                                     &horizontal_tracking_wheel, nullptr,
                                     &inertial_sensor);

// Input Scaling
lemlib::ExpoDriveCurve throttle_curve(3, 10, 1.019);
lemlib::ExpoDriveCurve steering_curve(3, 10, 1.019);

// LemLib Chassis (Drivetrain + PID + Odometry)
lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller,
                        odometry_sensors, &throttle_curve, &steering_curve);