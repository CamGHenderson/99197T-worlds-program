#include "DescoreAuton.h"
#include "Subsystems.h"
#include "ProgramArgs.h"
#include "AutonUtil.h" 
#include "api.h"

void descoreTriball()
{
	double iDistance = getRightDistance();
	double target = 10.0;
	double pError = 1.0;
	
	const double max = 80.0;
	const double min = 30.0;
	
	uint16_t count = 0;

	moveWings(RIGHT_WING, OPEN);
	while(pError > .05 || pError < -.05)
	{
		double error = target - (getRightDistance() - iDistance);
		pError = (error / target);
		if(pError > 1.0)
			pError = 1.0;
		
		int16_t speed = (pError * max);
		if(speed < min)
			speed = min;
		
		if(count >= 1000)
			moveWings(RIGHT_WING, CLOSED);
		
		count += LOOP_DELAY;
		
		setRightDriveVoltage(speed);
		delay(LOOP_DELAY);
	}
	
	setRightDriveVoltage(0);
	moveWings(RIGHT_WING, CLOSED);
	delay(750);
}

void scorePreload()
{
	setRightDriveVoltage(-100);
	setLeftDriveVoltage(-40);
	
	delay(400);
	
	setRightDriveVoltage(-100);
	setLeftDriveVoltage(-80);
	
	// implement imu collision shit here
	delay(800);
	
	setRightDriveVoltage(0);
	setLeftDriveVoltage(0);
	
	delay(500);
}

void waitForWallCollision()
{
	double iAngle = getRobotDirection();
	double currentAngle = iAngle;

	const double variance = 5.0;

	while(currentAngle < iAngle + variance && currentAngle > iAngle - variance)
	{
		currentAngle = getRobotDirection();
		delay(LOOP_DELAY);
	}
}

void goalSpacingMove()
{
	setRightDriveVoltage(80);
	setLeftDriveVoltage(80);

	delay(125);
	setRightDriveVoltage(0);
	setLeftDriveVoltage(0);
	delay(250);
}

void waitForBarHit()
{
	uint16_t count = 0;

	//(! &&

	while(isArmPressed())
	{
		//count += LOOP_DELAY;
		delay(LOOP_DELAY);
	}
	
	//delay(3000);
}

void pushAlleyTriballs()
{
	goalSpacingMove();
	adjustRelativeAngle(200.0, 50.0, 18.0);
		
	driveIntake(BACKWARDS);
	
	setRightDriveVoltage(50);
	setLeftDriveVoltage(50);
	delay(250);
	
	waitForWallCollision();
	
	adjustRelativeAngle(150.0, 35.0, 18.0);
	
	printRobotDirection();
	
	setRightDriveVoltage(40);
	setLeftDriveVoltage(40);

	delay(1500);
	setRightDriveVoltage(20);
	setLeftDriveVoltage(20);
	
	waitForBarHit();
	
	setRightDriveVoltage(0);
	setLeftDriveVoltage(0);
	
	delay(2000);
	
	driveIntake(NONE);
}

void runDescoreAuton()
{
	setRobotDirection(180);

	printRobotDirection();
	
	delay(250);
		
	descoreTriball();
	scorePreload();

	delay(500);
	
	//setRobotDirection(225);
	
	//printRobotDirection();
	pushAlleyTriballs();
	//printRobotDirection();
}
