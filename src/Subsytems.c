#include "Subsystems.h"
#include "api.h"

const double directionValues[3] = { 0.0, 1.0, -1.0 };

const int8_t driveMotors[DRIVE_MOTOR_COUNT] = { 
											-17, 18, -19, // left motors
										 	20, -5, 9  // right motors
										 };

const int8_t* leftDriveMotors = &driveMotors[0];
const int8_t* rightDriveMotors = &driveMotors[(DRIVE_MOTOR_COUNT / 2)]; 
 
const int8_t intakeMotors[INTAKE_MOTOR_COUNT] = { 15, -16 };
const char wings[2] = { 'A', 'B' };
const int8_t lift = 'C';

const uint8_t leftIMU = 11;
const uint8_t rightIMU = 13;

void initializeSubsystems()
{
	for(uint8_t i = 0; i < DRIVE_MOTOR_COUNT; i++)
	{
		int8_t port = driveMotors[i];
		
		if(port < 0)
		{
			port = abs(port);
			motor_set_reversed(port, true);
		}
		
		motor_set_encoder_units(port, E_MOTOR_ENCODER_ROTATIONS);
		motor_set_gearing(port, E_MOTOR_GEARSET_06);
		motor_tare_position(port);
	}
	
	for(uint8_t i = 0; i < INTAKE_MOTOR_COUNT; i++)
	{
		int8_t port = intakeMotors[i];
		
		if(port < 0)
		{
			port = abs(port);
			motor_set_reversed(port, true);
		}
	}
	
	// initialize wing adi
	adi_pin_mode('A', OUTPUT);
	adi_pin_mode('B', OUTPUT);
	adi_pin_mode('C', OUTPUT);
	
	adi_pin_mode('H', INPUT);
	
	imu_reset(leftIMU);
	imu_reset(rightIMU);
}

void setDriveSpeed(int16_t speed)
{
	for(uint8_t i = 0; i < DRIVE_MOTOR_COUNT; i++)
		motor_move_velocity(abs(driveMotors[i]), (speed * DRIVE_GEAR_RATIO));
}

void setLeftDriveSpeed(int16_t speed)
{
	for(uint8_t i = 0; i < DRIVE_MOTOR_COUNT / 2; i++)
		motor_move_velocity(abs(leftDriveMotors[i]), (int16_t)(speed * (1.0 / DRIVE_GEAR_RATIO)));
}

void setRightDriveSpeed(int16_t speed)
{
	for(uint8_t i = 0; i < DRIVE_MOTOR_COUNT / 2; i++)
		motor_move_velocity(abs(rightDriveMotors[i]), (int16_t)(speed * (1.0 / DRIVE_GEAR_RATIO)));
}

void setLeftDriveVoltage(int16_t voltage)
{
	for(uint8_t i = 0; i < DRIVE_MOTOR_COUNT / 2; i++)
		motor_move(abs(leftDriveMotors[i]), voltage);
}

void setRightDriveVoltage(int16_t voltage)
{
	for(uint8_t i = 0; i < DRIVE_MOTOR_COUNT / 2; i++)
		motor_move(abs(rightDriveMotors[i]), voltage);
}

double getLeftDistance()
{
	double r = 0.0;
	for(uint8_t i = 0; i < DRIVE_MOTOR_COUNT / 2; i++)
		r += motor_get_position(abs(leftDriveMotors[i]));
		
	return (r / 3.0) * WHEEL_CIRCUMFERENCE * DRIVE_GEAR_RATIO;
}

double getRightDistance()
{
	double r = 0.0;
	for(uint8_t i = 0; i < DRIVE_MOTOR_COUNT / 2; i++)
		r += motor_get_position(abs(rightDriveMotors[i]));

	return (r / 3.0) * WHEEL_CIRCUMFERENCE * DRIVE_GEAR_RATIO;
}

bool isLeftStalled()
{
	return motor_is_stopped(abs(leftDriveMotors[0]));
}

bool isRightStalled()
{
	return motor_is_stopped(abs(rightDriveMotors[0]));
}

double getLeftTorque()
{
	double sum = 0.0;
	for(uint16_t i = 0; i < DRIVE_MOTOR_COUNT / 2; i++)
		sum += motor_get_torque(leftDriveMotors[i]);

	return sum / (DRIVE_MOTOR_COUNT / 2);
}

double getRightTorque()
{
	double sum = 0.0;
	for(uint16_t i = 0; i < DRIVE_MOTOR_COUNT / 2; i++)
		sum += motor_get_torque(rightDriveMotors[i]);

	return sum / (DRIVE_MOTOR_COUNT / 2);
}

void driveIntake(Direction direction)
{
	for(uint8_t i = 0; i < INTAKE_MOTOR_COUNT; i++)
	{
		motor_move(abs(intakeMotors[i]), 127 * (int8_t)directionValues[direction]);
	}
}

int32_t getIntakeCurrentDraw()
{
	return motor_get_current_draw(intakeMotors[0]); 
}

void raiseLift()
{
	adi_digital_write(lift, true);
}

void lowerLift()
{
	adi_digital_write(lift, false);
}

void moveWings(WingSelection wingSelection, bool state)
{
	if(wingSelection == LEFT_WING || wingSelection == BOTH_WINGS)
	{
		adi_digital_write(wings[LEFT_WING], state);
		printf("%c, %i\n", wings[0], state);
	}	
		
	if(wingSelection == RIGHT_WING || wingSelection == BOTH_WINGS)
		adi_digital_write(wings[RIGHT_WING], state);
}

void setRobotDirection(double dir)
{
	imu_set_heading(leftIMU, dir - 90);
	imu_set_heading(rightIMU, dir + 90);
}

double getRobotDirection()
{
	double leftDir = imu_get_heading(leftIMU) - 90.0;
	double rightDir = imu_get_heading(rightIMU) + 90.0;
	double dir = (leftDir + rightDir) / 2.0;
	return dir;
}

bool isArmPressed()
{
	return !adi_digital_read('H');
}
