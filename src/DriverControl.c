#include "DriverControl.h"
#include "Subsystems.h"
#include "ProgramArgs.h"
#include "DescoreAuton.h"
#include "FarSideAuton.h"
#include "ScuffedUI.h"
#include "api.h"

void updateChassis()
{
	double lSpeed = (((double)controller_get_analog(E_CONTROLLER_MASTER, E_CONTROLLER_ANALOG_LEFT_Y)));
	double rSpeed = (((double)controller_get_analog(E_CONTROLLER_MASTER, E_CONTROLLER_ANALOG_RIGHT_Y)));
	
	setLeftDriveVoltage((int16_t)lSpeed);
	setRightDriveVoltage((int16_t)rSpeed);
}

void updateIntake()//TODO make toggle
{
	Direction dir;
	if(controller_get_analog(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_R2))
		dir = FORWARDS;	
	else if(controller_get_analog(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_R1))
		dir = BACKWARDS;
	else
		dir = NONE;
		
	driveIntake(dir);
}

void updateWings()
{
	static bool wingsDown = false;
	static bool bHold = false;

	if(controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_L1) ||
	   controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_L2))
	{
		if(!bHold)
		{
			wingsDown = !wingsDown;
			if(controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_L2))
				moveWings(RIGHT_WING, wingsDown);
			else
				moveWings(BOTH_WINGS, wingsDown);
			
			bHold = true;
		}
	}
	else
		bHold = false;
}

void updateLift()
{
	static bool deployed = false;
	static bool bHold = false;
	if(controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_A))
	{
		if(!bHold)
		{
			deployed = !deployed;
			bHold = true;
			
			(deployed ? raiseLift() : lowerLift());
		}
	}
	else
		bHold = false;	
}

void runDriverControl()
{
	while(true)
	{
		if(controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_DOWN))
		{
			// garbage
			if(getUISelection() == UI_CLOSE_AUTO)
				runDescoreAuton();	
			else if(getUISelection() == UI_FAR_AUTO)
				runFarSideAuton();
			else
				runFarSideAuton();
				
			//runDescoreAuton();
		}
		
		updateChassis();
		updateIntake();
		updateWings();
		updateLift();
		
		delay(LOOP_DELAY);
	}
}
