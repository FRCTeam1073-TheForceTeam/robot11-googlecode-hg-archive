//////////////////////////////////////////////////////////
// Filename: Dashboardender.h
// Author:   
// Date:     January 23, 2011
//
// Description: This file contains class defintion for the DashBoardSender responible for sending all data 
// to the custom dashboard.
//
//////////////////////////////////////////////////////////
#ifndef DASHBOARDSENDER_H_
#define DASHBOARDSENDER_H_

#include "userincludes.h"

class DashboardSender;
class Encoders1073;
class SmartJoystick;
class SmartGyro;

class DashboardSender
{
	public:
		
		DashboardSender(DriverStation *dash, Encoders1073 *enc, SmartJoystick *lJoystick, SmartJoystick *rJoystick, SmartGyro *gyr);
		void SendData(void);
		void SendConstants(void);

	private:
		DriverStation *ds;
		Encoders1073 *encoders;
		SmartJoystick *leftJoystick;
		SmartJoystick *rightJoystick;
		SmartGyro *gyro;
};

#endif
