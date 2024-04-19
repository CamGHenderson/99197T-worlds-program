#include "DescoreAuton.h"
#include "Subsystems.h"
#include "ProgramArgs.h"
#include "AutonUtil.h" 
#include "api.h"

void descoreTriball()
{
	double iDistance = getRightDistance();
	double target = 14.0;//inches
	double pError = 1.0;//percent error
	
	const double max = 80.0;
	const double min = 30.0;
	
	uint16_t count = 0;

	moveWings(RIGHT_WING, OPEN);
	while(pError > .05 || pError < -.05)//if its within 5% of target distance (0.05)
	{
		double error = target - (getRightDistance() - iDistance);//target - change in distance = how far to get to goal
		pError = (error / target);
		if(pError > 1.0)//make sure it doesnt go over 100%
			pError = 1.0;
		
		int16_t speed = (pError * max);//speed is voltage, taking max speed and getting part by multoply by percent
		if(speed < min)//prevents motors from stalling
			speed = min;
		
		if(count >= 1000)//close wing 1 sec (1000ms) after start
			moveWings(RIGHT_WING, CLOSED);
		
		count += LOOP_DELAY;
		
		setRightDriveVoltage(speed);//setting motors to speed
		delay(LOOP_DELAY);
	}
	
	setRightDriveVoltage(0);
	delay(750);
}

void scorePreload()//pretty much sensorless
{
	setRightDriveVoltage(-100);
	setLeftDriveVoltage(-40);
	
	delay(400);
	
	setRightDriveVoltage(-127);
	setLeftDriveVoltage(-95);
	
	// implement imu collision shit here
	delay(1000);
	
	setRightDriveVoltage(0);
	setLeftDriveVoltage(0);
	
	delay(500);
}

void waitForWallCollision()
{
	double iAngle = getRobotDirection();
	double currentAngle = iAngle;

	const double variance = 8.0;

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
	adjustRelativeAngle(190.0, 50.0, 25.0);
	driveIntake(BACKWARDS);
	
	setRightDriveVoltage(50);
	setLeftDriveVoltage(50);
	delay(300);
	
	waitForWallCollision();
	
	adjustRelativeAngle(150.0, 50.0, 25.0);
	
	printRobotDirection();
	
	setRightDriveVoltage(40);
	setLeftDriveVoltage(40);

	delay(1500);
	setRightDriveVoltage(20);
	setLeftDriveVoltage(20);
	
	waitForBarHit();
	
	//delay(0);
	
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
