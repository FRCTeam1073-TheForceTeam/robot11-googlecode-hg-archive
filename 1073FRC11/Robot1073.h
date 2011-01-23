#ifndef ROBOT1073_H_
#define ROBOT1073_H_

#include "wpilib.h"
#include "userincludes.h"
#include "LNDrive.h"
#include "Navigation.h"
#include "Minibot.h"
#include "DashboardSender.h"
#include "DriverMessages.h"
#include "cameramanager.h"

class Robot1073;

class Robot1073: public SimpleRobot
{
	public:
		
		Robot1073();
		void Autonomous();
		void OperatorControl();
		void ZombieZonePeriodicService();
	
	private:

		AxisCamera &camera;          // This reference syntax necessary because of the referance associated with GetInstance().
		DriverStation *driverStation;
		Jaguar *leftMotorJaguar;
		Jaguar *rightMotorJaguar;
		Joystick *leftJoystick;
		Joystick *rightJoystick;
		Encoder *leftEncoder;
		Encoder *rightEncoder;
		Accelerometer *xAxisAccelerometer;
		Accelerometer *yAxisAccelerometer;
		Gyro *gyro;
		
		Navigation *navigation;
		LNDrive *drive;
		Minibot *minibot;
		DashboardSender *dashboardSender;
		DriverMessages *driverMessages;
		CameraManager *cameraManager;
		
		void InitializeTheZombieZone(Robot1073 *ptr);

};



#endif


