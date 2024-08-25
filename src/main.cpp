#include "main.h"
#include "lemlib/api.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/misc.h"
#include "pros/rotation.hpp"

// TODO: Software-Side
// 1. Perform PID Tuning

// TODO: Hardware-Side
// 1. Add vertical/horizontal tracking wheels (would make my life a lot easier)

// Smart Port Devices
pros::MotorGroup
    left_motors({1, 2, 3},
                pros::MotorGearset::green);
pros::MotorGroup
    right_motors({-4, -5, -6},
                 pros::MotorGearset::green);


pros::Rotation horizontal_rotation_sensor(9);
pros::Rotation vertical_rotation_sensor(10);
pros::Imu inertial_sensor(7);

// 3-Wire Devices
pros::adi::DigitalOut grabber_piston ('a', LOW);

// Wireless Devices
pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::Controller partner_controller(pros::E_CONTROLLER_PARTNER);

// Drivetrain Configuration
lemlib::Drivetrain
    drivetrain(&left_motors, &right_motors,
               11.75,
               lemlib::Omniwheel::NEW_275,
               360, // Drivetrain Speed (RPM) TODO: Tune this value
               2    // Horizontal Drift TODO: Tune this value
    );

// PID Tuning
lemlib::ControllerSettings
    lateral_controller(10,  // proportional gain (kP)
                       0,   // integral gain (kI)
                       3,   // derivative gain (kD)
                       3,   // anti windup
                       1,   // small error range, in inches
                       100, // small error range timeout, in milliseconds
                       3,   // large error range, in inches
                       500, // large error range timeout, in milliseconds
                       20   // maximum acceleration (slew)
    );

lemlib::ControllerSettings
    angular_controller(2,   // proportional gain (kP)
                       0,   // integral gain (kI)
                       10,  // derivative gain (kD)
                       3,   // anti windup
                       1,   // small error range, in degrees
                       100, // small error range timeout, in milliseconds
                       3,   // large error range, in degrees
                       500, // large error range timeout, in milliseconds
                       0    // maximum acceleration (slew)
    );

// Odometry Configuration
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_rotation_sensor, lemlib::Omniwheel::OLD_275, -2);
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_rotation_sensor, lemlib::Omniwheel::OLD_275, -0.75);


lemlib::OdomSensors odometry_sensors(&vertical_tracking_wheel, // Vertical Tracking Wheel 1
                                     nullptr, // Vertical Tracking Wheel 2
                                     &horizontal_tracking_wheel, // Horizontal Tracking Wheel 1
                                     nullptr, // Horizontal Tracking Wheel 2
                                     &inertial_sensor // Inertial Sensor
);

// Input Scaling
lemlib::ExpoDriveCurve throttle_curve(3, 10, 1.019);
lemlib::ExpoDriveCurve steering_curve(3, 10, 1.019);

// LemLib Chassis (Drivetrain + PID + Odometry)
lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller,
                        odometry_sensors, &throttle_curve, &steering_curve);

void initialize() {
	// Initialize screen
	pros::lcd::initialize();

	// Calibrate Sensors
	chassis.calibrate(true);

	// Log position to screen (for debugging)
	pros::Task position_logging_task([&]() {
		// Print Position
		pros::lcd::print(0, "X: %f", chassis.getPose().x);
		pros::lcd::print(1, "Y: %f", chassis.getPose().y);

		// Print Heading
		pros::lcd::print(2, "Heading: %f", chassis.getPose().theta);

		// Sleep for 20ms (give screen enough time to update)
		pros::delay(20);
	});
}


void disabled() {}
void competition_initialize() {}
void autonomous() {}
void opcontrol() {
	// Arcade Style Control (speed + direction) // TODO: Choose preffered control (tank, arcade, curvature)
	while (true) {
		// Get controller inputs
		int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		// Move the robot (with steering priority)
		chassis.arcade(leftY, rightX, false, 0.75); // High value = prioritize steering, low value = prioritize speed

        // Pneumatics
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
            grabber_piston.set_value(HIGH);
        }
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
            grabber_piston.set_value(LOW);
        }

		// Sleep for 20ms (save resources, no need to update faster)
		pros::delay(20);
	}

}