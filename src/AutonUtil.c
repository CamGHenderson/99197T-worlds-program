#include "AutonUtil.h"
#include "Subsystems.h"
#include "api.h"
#include "ProgramArgs.h"
#include <stdint.h>

void adjustRelativeAngle(const double optimalAngle, const double topSpeed, const double min)
{
	const double maxMotorTorque = 0.7;

	double pError = 1.0;
	uint16_t restCount = 0;
	
	while(true)
	{
		pError = (optimalAngle - getRobotDirection()) / 45.0;//move at full speed if greater than 45o
		if(pError > 1.0)//makes it full speed if angle greater than 45. (>45/45 = >1)
			pError = 1.0;

		int16_t speed = (int16_t)(pError * topSpeed);
		int16_t sign = (speed / abs(speed));
		if(abs(speed) < min)
			speed = min * sign;

		double pTorqueAve = abs((getLeftTorque() + getRightTorque()) / 2.0) / maxMotorTorque;
		if(pTorqueAve >= maxMotorTorque && pError < 0.1)
		{
			
		}
		
		// ensure robot is within acceptable error and at rest
		if(pError < 0.05 && pError > -.05)//be within 5% for 100 ms before break, helps prevent overshoot
		{
			restCount++;
			speed = 0;
		}
		else
			restCount = 0;
		
		if(restCount >= 10)
			break;
		
		setRightDriveVoltage(-speed);
		setLeftDriveVoltage(speed);

		delay(LOOP_DELAY);	
	}
	
	delay(100.0);
}

void printRobotDirection()
{
	printf("Robot Heading: %f\n", getRobotDirection());
}
