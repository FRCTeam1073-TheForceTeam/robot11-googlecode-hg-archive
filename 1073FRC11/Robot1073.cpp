//////////////////////////////////////////////////////////
// Filename: Robot1073.cpp
// Author:   
// Date:     January 23, 2011
//
// Description: This file contains the main defintion for the Team1073 Robot.
//
//////////////////////////////////////////////////////////
#include "Robot1073.h"


Robot1073::Robot1073(void)
: camera (AxisCamera::GetInstance())					// This initialization syntax necessary because of the referance associated with GetInstance().

{
	cameraManager = new CameraManager();
	driverStation = DriverStation::GetInstance();

#if 1
	leftMotorJaguar = new Jaguar(PWM_LeftMotorPort);
	rightMotorJaguar = new Jaguar(PWM_RightMotorPort);
#else
	leftMotorJaguar = new CANJaguar(PWM_LeftMotorPort);
	rightMotorJaguar = new CANJaguar(PWM_RightMotorPort);
	
#endif
	
	// Should rev
	
	leftJoystick = new Joystick(USB_LeftJoystickPort);
	rightJoystick = new Joystick(USB_RightJoystickPort);
	
	leftEncoder = new Encoder(DIO_LeftEncoderAPort, DIO_LeftEncoderBPort);
	rightEncoder = new Encoder(DIO_RightEncoderAPort, DIO_RightEncoderBPort);
	
	
	gyro = new Gyro(ANALOG_GyroPort);
	xAxisAccelerometer = new Accelerometer(ANALOG_XAxisAccelerometerPort);
	yAxisAccelerometer = new Accelerometer(ANALOG_YAxisAccelerometerPort);
	timer = new Timer();
	
	navigation = new Navigation(leftEncoder, rightEncoder, xAxisAccelerometer, yAxisAccelerometer, gyro, timer);
	drive = new LNDrive(leftMotorJaguar, rightMotorJaguar, leftJoystick, rightJoystick, navigation);
	minibot = new Minibot();
	dashboardSender = new DashboardSender(driverStation,leftEncoder,rightEncoder,leftJoystick,rightJoystick, gyro);
	driverMessages = new DriverMessages(leftJoystick, gyro);
	cameraManager->StartCamera();
	
	InitializeTheZombieZone(this);
	
}

void Robot1073::Autonomous(void)
{
	
}

void Robot1073::OperatorControl(void)
{
	
	while (IsOperatorControl())
	{
		drive->PeriodicService();
		navigation->PeriodicService();
		Wait(WaitTime);				// wait for a motor update time
	}
}



void Robot1073::ZombieZonePeriodicService()
{
		dashboardSender->SendData();
		driverMessages->PeriodicService();
}


START_ROBOT_CLASS(Robot1073);





