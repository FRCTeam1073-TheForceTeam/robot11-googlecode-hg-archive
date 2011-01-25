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


class DriverMessages;

class DriverMessages
{
	public:
		DriverMessages(Joystick *joystick, Gyro *gyroPtr);
		void PeriodicService();
		
		
		void PrintIt(int line, char *fmt, ...);
		void SendTextLines();
		
	private:
		int displayIndex;
		Joystick *menuJoystick;
		Gyro *gyro;
		char lineText[10][81];	// Let's reserve space for 4 lines of 81 characters each
			
			
};


#endif
