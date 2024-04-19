#include "FarSideAuton.h"
#include "Subsystems.h"
#include "AutonUtil.h"
#include "ProgramArgs.h"
#include "api.h"

void waitForTriballCollection()
{
	while(true)
	{
		if(getIntakeCurrentDraw() > 2360)
			break;
		
		delay(LOOP_DELAY);		
	}
}

void collectFirstTriball()
{
	printRobotDirection();

	driveIntake(FORWARDS);
	delay(100);
	
	setRightDriveVoltage(25);
	setLeftDriveVoltage(25);
	
	waitForTriballCollection();
	delay(180);
	
	setRightDriveVoltage(0);
	setLeftDriveVoltage(0);
	
	driveIntake(NONE);
	
	delay(500);
	
	adjustRelativeAngle(185.0, 40, 18.0);
	
	delay(500);
	
	printRobotDirection();
}

// descore triball (c is angry)
void sweepTriballs()
{
	setRightDriveVoltage(-40);
	setLeftDriveVoltage(-38);
	
	delay(2500);
	
	setRightDriveVoltage(0);
	setLeftDriveVoltage(0);
	
	delay(250);
	
	// this may be the source of the really fucked bug
	adjustRelativeAngle(140.0, 80.0, 30.0);
	
	moveWings(BOTH_WINGS, OPEN);
	
	// add prop controller here
	setRightDriveVoltage(-40);
	setLeftDriveVoltage(-40);
	
	delay(975);
	
	adjustRelativeAngle(90.0, 50.0, 20.0);
	
	setRightDriveVoltage(-100);
	setLeftDriveVoltage(-127);
	
	delay(1100);
	
	moveWings(BOTH_WINGS, CLOSED);
	
	setRightDriveVoltage(0);
	setLeftDriveVoltage(0);
}

void runFarSideAuton()
{
	setRobotDirection(180.0);
	collectFirstTriball();
	sweepTriballs();
}
