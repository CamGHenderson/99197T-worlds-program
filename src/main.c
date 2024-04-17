#include "main.h"
#include "Subsystems.h"
#include "DriverControl.h"
#include "DescoreAuton.h"
#include "FarSideAuton.h"
#include "ScuffedUI.h"

void initialize()
{
	initializeSubsystems();
	displayAutoMenu();
}

void autonomous()
{	
	if(getUISelection() == UI_CLOSE_AUTO)
		runDescoreAuton();	
	else if(getUISelection() == UI_FAR_AUTO)
		runFarSideAuton();
}

void opcontrol()
{
	runDriverControl();
}
