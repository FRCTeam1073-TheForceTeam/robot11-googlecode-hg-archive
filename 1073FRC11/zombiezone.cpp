#include "math.h"  
#include "Robot1073.h"


/*****************************************************************************************************
 *  Zombie Zone --> Is the intermediate life outside of Autonomous and Teleoperated allowing background of our software prior to 
 *     Autonomous and teleoperated modes.  Continues life even when disabled....
 *     1) Dashboard data sends
 * 	   2) Menu Controls and updates
 * 	   3) LCD display updates
 * 	   4) Diagnostic updates
 *  
 * *****************************************************************************************************/



// This important static is to allow our launched TwilightZone thread to access our main Robot class member functions.
// This static (not quite a global) is used exclusively to call the main bots TwilightZonePeriodicServics().
static Robot1073 *robot1073;
const float periodicIntervalSec = .05;

int
ZombieFunction()
{
	while (1)				// Run this loop forever once launched...
	{
		Wait(periodicIntervalSec);		// Wait 50ms for a 20Hz update rate...
		robot1073->ZombieZonePeriodicService();	
	}
}



SEM_ID ZombieSemaphore = 0;
Task *ZombieTask;
void
Robot1073::InitializeTheZombieZone(Robot1073 *ptr)
{
	printf("Zombie Initiation ocurred\n");
	robot1073 = ptr;
	ZombieTask = new Task("ZombieFunction", (FUNCPTR)ZombieFunction );
	ZombieSemaphore = semMCreate(SEM_DELETE_SAFE | SEM_INVERSION_SAFE); // synchronize access to multi-value registers
	ZombieTask->Start();
}
