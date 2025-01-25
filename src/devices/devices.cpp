#include "devices.hpp"
#include "lemlib/chassis/trackingWheel.hpp"

// Smart Port Devices
// 1: Right Motor 1
// 2: Right Motor 2
// 3: Right Motor 3
// 4: *Empty*
// 5: *Empty*
// 6: *Empty*
// 7: Inertial Sensor
// 8: Horizontal Rotation Sensor
// 9: *Empty*
// 10: *Empty*
// 11: Vertical Rotation Sensor
// 12: Intake Belt
// 13: Intake Rollers
// 14: *Empty*
// 15: Optical Sensor
// 16: *Empty*
// 17: *Empty*
// 18: Left Motor 1
// 19: Left Motor 2
// 20: Left Motor 3
// 21: Radio
pros::MotorGroup left_motors({-18, -19, -20}, pros::MotorGearset::green);
pros::MotorGroup right_motors({1, 2, 3}, pros::MotorGearset::green);

pros::Imu inertial_sensor(7);
pros::Rotation horizontal_rotation_sensor(8);
pros::Rotation vertical_rotation_sensor(-11);

pros::MotorGroup intake_belt({12}, pros::MotorGearset::blue);
pros::MotorGroup intake_rollers({-13}, pros::MotorGearset::green);

pros::Optical optical_sensor(15);

// 3-Wire Devices
// A: Grabber Piston
// B: Lift Piston
// C: Arm
// D: *Empty*
// E: *Empty*
// F: *Empty*
// G: *Empty*
// H: *Empty*
pros::adi::DigitalOut grabber_piston('A', LOW);
pros::adi::DigitalOut lift_piston('B', LOW);
pros::adi::DigitalOut arm('C', LOW);


// Wireless Devices
pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::Controller partner_controller(pros::E_CONTROLLER_PARTNER);

// Drivetrain Configuration
lemlib::Drivetrain drivetrain(&left_motors, &right_motors, 13.25,
                              lemlib::Omniwheel::NEW_275, 360, 2);

// PID Tuning
lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

lemlib::ControllerSettings angular_controller(3, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              12, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// Odometry Configuration
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_rotation_sensor,
                                                lemlib::Omniwheel::NEW_2, -2.5); // 2 3/4 inches back
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_rotation_sensor,
                                              lemlib::Omniwheel::NEW_2,
                                              -1.125); // 1 1/8 inches left

lemlib::OdomSensors odometry_sensors(&vertical_tracking_wheel, nullptr,
                                     &horizontal_tracking_wheel, nullptr,
                                     &inertial_sensor);

// Input Scaling
lemlib::ExpoDriveCurve throttle_curve(3, 10, 1.019);
lemlib::ExpoDriveCurve steering_curve(3, 10, 1.019);

// LemLib Chassis (Drivetrain + PID + Odometry)
lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller,
                        odometry_sensors, &throttle_curve, &steering_curve);