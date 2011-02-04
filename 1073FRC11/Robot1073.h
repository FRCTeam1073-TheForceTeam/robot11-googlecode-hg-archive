#ifndef ROBOT1073_H_
#define ROBOT1073_H_
#include "wpilib.h"
#include "userincludes.h"
#include "LNDrive.h"
#include "Navigation.h"
#include "Minibot.h"
#include "DashboardSender.h"
#include "DashboardReceiver.h"
#include "LineFollower.h"
//////////////////////////////////////////////////////////
// Filename: Robot1073.h
// Author:   
// Date:     January 23, 2011
//
// Description: This file contains the main defintion for the Team1073 Robot.
//
//////////////////////////////////////////////////////////
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
		SpeedController *leftMotorJaguar;
		SpeedController *rightMotorJaguar;
		Joystick *leftJoystick;
		Joystick *rightJoystick;
		Encoder *leftEncoder;
		Encoder *rightEncoder;
		Accelerometer *xAxisAccelerometer;
		Accelerometer *yAxisAccelerometer;
		Gyro *gyro;
		Timer *timer;
		Navigation *navigation;
		LNDrive *drive;
		Minibot *minibot;
		DashboardSender *dashboardSender;
		DashboardReceiver *dashboardReceiver;
		DriverMessages *driverMessages;
		CameraManager *cameraManager;
		DigitalInput *leftLineSensor;
		DigitalInput *middleLineSensor;
		DigitalInput *rightLineSensor;
		LineFollower *lineFollower;
		
		void InitializeTheZombieZone(Robot1073 *ptr);
		void InitializeDashboardReceiverThread(Robot1073 *, DashboardReceiver *);
		void ResetEncoders();
		void InitEncoders();

};


#endif

