#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#define DRIVE_MOTOR_COUNT 6
#define INTAKE_MOTOR_COUNT 2

#define DRIVE_GEAR_RATIO (3.0 / 5.0)
#define WHEEL_CIRCUMFERENCE M_PI * 3.25 

#define OPEN true
#define CLOSED false

typedef enum
{
	NONE = 0,
	FORWARDS = 1,
	BACKWARDS = 2,
} Direction;

typedef enum
{
	RIGHT_WING = 0,
	LEFT_WING = 1,
	BOTH_WINGS = 2
} WingSelection;

void initializeSubsystems();

void setDriveSpeed(int16_t speed);
void setLeftDriveSpeed(int16_t speed);
void setRightDriveSpeed(int16_t speed);
void setLeftDriveVoltage(int16_t voltage);
void setRightDriveVoltage(int16_t voltage);
bool isLeftStalled();
bool isRightStalled();
double getLeftDistance();
double getRightDistance();
double getLeftTorque();
double getRightTorque();

void driveIntake(Direction direction);
int32_t getIntakeCurrentDraw();

void raiseLift();
void lowerLift();
void moveWings(WingSelection selection, bool state);

void setRobotDirection(double dir);
double getRobotDirection();

bool isArmPressed();

