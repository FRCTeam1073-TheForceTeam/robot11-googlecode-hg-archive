#ifndef DRIVERMESSAGES_H_
#define DRIVERMESSAGES_H_

#include "userincludes.h"


class DriverMessages;

class DriverMessages
{
	public:
		DriverMessages(Joystick *joystick);
		void PeriodicService();
		
		
		void PrintIt(int line, char *fmt, ...);
		void SendTextLines();
		
	private:
		int displayIndex;
		Joystick *menuJoystick;
		char lineText[10][81];	// Let's reserve space for 4 lines of 81 characters each
			
			
};


#endif
