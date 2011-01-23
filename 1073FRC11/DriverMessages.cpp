#include "drivermessages.h"


DriverMessages::DriverMessages(Joystick *jStick, Gyro *gyroPtr)
{
	menuJoystick = jStick;
	gyro = gyroPtr;
	displayIndex = 0;
}

void DriverMessages::PeriodicService()
{
	bool isButtonSixPressed = menuJoystick->GetRawButton(6);
	static bool wasButtonSixPressed = false;
	
	
	
	float xVal = menuJoystick->GetX();
	float yVal = menuJoystick->GetY();
	
	
	switch(displayIndex){
	
	case 0:		PrintIt(0, "Joystick Test");
				PrintIt(1, "X%6.3f Y%6.3f",xVal, yVal);
				break;
	case 1:     PrintIt(0, "Gyro=%3.5f", gyro->GetAngle());
				break;
				
				
	}
	SendTextLines();
	
	
	if(isButtonSixPressed && !wasButtonSixPressed){   	// Is the button currently pressed
		displayIndex += 1;		// Set bext display count.
		if(displayIndex > 1){
			displayIndex = 0;
		}
	}
	wasButtonSixPressed = isButtonSixPressed;
}

void
DriverMessages::SendTextLines()
{
	DriverStationLCD *lcd =DriverStationLCD::GetInstance();
	
	for(int i = 0; i < 3;i++){
			lcd->Printf((DriverStationLCD::Line)i, 1, "%s", (char *)lineText[i]);
	}
	lcd->UpdateLCD();
	
}


void
DriverMessages::PrintIt(int lineIndex, char *fmt, ...)
{
  va_list       args;
  va_start (args, fmt);

  if(lineIndex < 0 or lineIndex > 6)
	  return;
  if(lineIndex == 0){		// If printing the first line, then assume 1,2, & 3 are blanked
	  for(int i = 0; i < 3; i++){
		  strcpy((char *)lineText[i], "                     ");
	  }
  }
  
  vsprintf (lineText[lineIndex], fmt, args);
  strcat(lineText[lineIndex], "                     ");
  va_end (args);

	
}
