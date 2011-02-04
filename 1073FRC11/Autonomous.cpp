//////////////////////////////////////////////////////////
// Filename: Autonomous.cpp
// Author:   
// Date:     February 2, 2011
//
// Description: This file contains the main defintion for the Team1073 Robot.
//
//////////////////////////////////////////////////////////
#include "Robot1073.h"
void Robot1073::Autonomous(void)
{
	encoders->ResetEncoders();
	
	while (IsAutonomous())
	{
		navigation->PeriodicService();
		lineFollower->PeriodicService();
		Wait(WaitTime);				// wait for a motor update time
	}

	
	
}
