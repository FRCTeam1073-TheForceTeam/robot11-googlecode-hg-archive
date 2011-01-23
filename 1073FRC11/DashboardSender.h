#ifndef DASHBOARDSENDER_H_
#define DASHBOARDSENDER_H_

#include "userincludes.h"

class DashboardSender;

class DashboardSender
{
	public:
		
		DashboardSender(DriverStation *dash, Encoder *lEncoder, Encoder *rEncoder, Joystick *lJoystick, Joystick *rJoystick, Gyro *gyr);
		void SendData(void);
		void SendIODiagnosticStuff(void);

	private:
		DriverStation *ds;
		Encoder *leftEncoder;
		Encoder *rightEncoder;
		Joystick *leftJoystick;
		Joystick *rightJoystick;
		Gyro *gyro;
};

#endif
