#ifndef ROBOT1073_H_
#define ROBOT1073_H_
#include "userincludes.h"
#include "LNDrive.h"
#include "Navigation.h"
#include "Minibot.h"
#include "DashboardSender.h"
class Robot1073;
class Robot1073: public SimpleRobot
{
	public:
		Robot1073();
		void Autonomous();
		void OperatorControl();
	private:
		Jaguar *leftMotorJaguar;
		Jaguar *rightMotorJaguar;
		Joystick *leftJoystick;
		Joystick *rightJoystick;
		Encoder *leftEncoder;
		Encoder *rightEncoder;
		Accelerometer *accel;
		Gyro *gyro;
		Navigation *navigation;
		LNDrive *drive;
		Minibot *minibot;
		DashboardSender *dashboardSender;
};
#endif
START_ROBOT_CLASS(Robot1073);
