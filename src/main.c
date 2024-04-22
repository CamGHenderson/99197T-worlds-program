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
	runDescoreAuton();
}

void opcontrol()
{
	runDriverControl();
}
