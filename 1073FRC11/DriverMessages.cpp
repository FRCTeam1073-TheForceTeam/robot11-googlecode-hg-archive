#include "drivermessages.h"


DriverMessages::DriverMessages(Joystick *jStick, Gyro *gyroPtr, Encoder *lEncoder, Encoder *rEncoder)
{
	menuJoystick = jStick;
	gyro = gyroPtr;
	leftEncoder = lEncoder;
	rightEncoder = rEncoder;
	displayIndex = 2;
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
	case 2:     PrintIt(0, "Encoders:");
	 			PrintIt(1, "l:%f", leftEncoder->GetDistance());
	 			PrintIt(2, "r:%f", rightEncoder->GetDistance());
				break;

	// Should not get here ever, display index not properly range checked below...
	default:	PrintIt(0,"Bad Index!!!!");
				break;
	}
	SendTextLines();
	
	
	if(isButtonSixPressed && !wasButtonSixPressed){   	// Is the button currently pressed
		displayIndex += 1;		// Set bext display count.
		if(displayIndex > 2){   // Increment the value until the last number in case statemen
			displayIndex = 0;	// Cycle back to the 0th index
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

  if ((lineIndex < 0) || (lineIndex > 6))
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
