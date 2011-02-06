//////////////////////////////////////////////////////////
// Filename: DriverMessage.h
// Author:   
// Date:     January 24, 2011
//
// 
//
//////////////////////////////////////////////////////////
#ifndef DRIVERMESSAGES_H_
#define DRIVERMESSAGES_H_

#include "userincludes.h"
#include "Navigation.h"
#include "SmartGyro.h"
#include "SmartJoystick.h"


class DriverMessages;
class Encoders1073;

class DriverMessages
{
	public:
		DriverMessages(SmartJoystick *joystick, SmartGyro *gyroPtr, Encoders1073 *encoders, Navigation *nav);
		void PeriodicService();
		
		
		void PrintIt(int line, char *fmt, ...);
		void SendTextLines();
		
	private:
		int displayIndex;
		SmartJoystick *menuJoystick;
		SmartGyro *gyro;
		Encoders1073 *encoders;
		Navigation *navigation;
		char lineText[10][81];	// Let's reserve space for 4 lines of 81 characters each
			
			
};


#endif
