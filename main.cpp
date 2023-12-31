#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
#include "main.h"
//#define DIGITAL_SENSOR_PORT_A 'A'
//#define DIGITAL_SENSOR_PORT_B 'B'

void opcontrol();
	
	pros::Controller master (CONTROLLER_MASTER);
	
	pros::Motor left1 (18, MOTOR_GEARSET_18, false);
	pros::Motor left2 (20, MOTOR_GEARSET_18, false);
	pros::Motor right1 (8, MOTOR_GEARSET_18, false);
	pros::Motor right2 (10, MOTOR_GEARSET_18, false);

	pros::Motor intake (15, MOTOR_GEARSET_18, false);

	bool transistion = false;

//thanks to team
/*
ports

left1 is 18
left2 is 20
intake is 15
right1 is 8
right2 is 10
*/

	while (true) {

		int left1Control = master.get_analog(ANALOG_LEFT_Y)-master.get_analog(ANALOG_LEFT_X);
		int left2Control = master.get_analog(ANALOG_LEFT_Y)-master.get_analog(ANALOG_LEFT_X);

		int right1Control = (-master.get_analog(ANALOG_LEFT_Y))-(master.get_analog(ANALOG_LEFT_X));
		int right2Control = (-master.get_analog(ANALOG_LEFT_Y))-(master.get_analog(ANALOG_LEFT_X));


		left1.move(left1Control);
		left2.move(left2Control);

		right1.move(right1Control);
		right2.move(right2Control);

		if (master.get_digital(DIGITAL_R1)) {
		intake.move_velocity(100); // This is 100 because it's a 100rpm motor
		}
		else if (master.get_digital(DIGITAL_R2)) {
		intake.move_velocity(-100);
		}
		else {
		intake.move_velocity(0);
		}

		pros::delay(2);

		//upload command is
/*
sudo usermod -a -G tty $USER
sudo usermod -a -G dialout $USE
sudo usermod -a -G tty $USER
/sbin/agetty -L -f /etc/issueserial 9600 ttyS0 vt100
sudo prosv5 upload
*/
	}
}
