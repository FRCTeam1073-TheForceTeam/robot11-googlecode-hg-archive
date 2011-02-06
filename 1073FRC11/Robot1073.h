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
#include "Encoders1073.h"
#include "SmartJoystick.h"
#include "SmartJagMotor.h"
#include "SmartGyro.h"

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
		
		// Pointers for each of 6 Jaguar Motots
		CANJaguar *leftMotorJaguar;
		CANJaguar *rightMotorJaguar;
		CANJaguar *pincerJaguar;
		CANJaguar *armJaguar;
		SmartJaguarMotorEncoder *elevatorJaguarMotorA;
		SmartJaguarMotorEncoder *elevatorJaguarMotorB;
		
		SmartJoystick *leftJoystick;
		SmartJoystick *rightJoystick;
		Encoders1073 *encoders;
		
		ADXL345_I2C *accelerometer;
		SmartGyro *gyro;
		Servo *servo;
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
};


#endif

