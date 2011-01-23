#include "drivermessages.h"


DriverMessages::DriverMessages(Joystick *jStick)
{
	menuJoystick = jStick;
	displayIndex = 0;
}

void DriverMessages::PeriodicService()
{
	bool isButtonOnePressed = menuJoystick->GetRawButton(1);
	float xVal = menuJoystick->GetX();
	float yVal = menuJoystick->GetY();
	
	PrintIt(0, "JoyStick Test: Button = %s", isButtonOnePressed ? "Pressed" : "Not");
	PrintIt(1, "X --> %6.3f Y --> %6.3f",xVal, yVal); 
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
