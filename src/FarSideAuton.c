#include "FarSideAuton.h"
#include "Subsystems.h"
#include "AutonUtil.h"
#include "ProgramArgs.h"
#include "api.h"

void descoreFar()
{
	double iDistance = getLeftDistance();
	double target = 14.0;//inches
	double pError = 1.0;//percent error
	
	const double max = 80.0;
	const double min = 30.0;
	
	uint16_t count = 0;

	moveWings(LEFT_WING, OPEN);
	
	delay(1000);
	
	while(pError > .05 || pError < -.05)//if its within 5% of target distance (0.05)
	{
		double error = target - (getLeftDistance() - iDistance);//target - change in distance = how far to get to goal
		pError = (error / target);
		if(pError > 1.0)//make sure it doesnt go over 100%
			pError = 1.0;
		
		int16_t speed = (pError * max);//speed is voltage, taking max speed and getting part by multiply by percent
		if(speed < min)//prevents motors from stalling
			speed = min;
		
		if(count >= 1000)//close wing 1 sec (1000ms) after start
			moveWings(LEFT_WING, CLOSED);
		
		count += LOOP_DELAY;
		
		setLeftDriveVoltage(speed);//setting motors to speed
		delay(LOOP_DELAY);
	}
	
	moveWings(LEFT_WING, CLOSED);
	
	setRightDriveVoltage(0);
	delay(750);

	
}	

void scorePreloadFar()
{
	setLeftDriveVoltage(-100);
	setRightDriveVoltage(-40);
	
	delay(400);
	
	setLeftDriveVoltage(-127);
	setRightDriveVoltage(-95);
	
	delay(1000);
	
	setRightDriveVoltage(0);
	setLeftDriveVoltage(0);
	
	delay(500);
}

void runFarSideAuton()
{
	setRobotDirection(180.0);

	descoreFar();

	//scorePreloadFar();
}
