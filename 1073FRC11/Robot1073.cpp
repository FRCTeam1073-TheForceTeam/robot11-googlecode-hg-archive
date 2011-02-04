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

	
// Both the PWM & CAN Jaguars are suportable with this simple comple time option...	
	leftMotorJaguar = new CANJaguar(CAN_LeftMotorAddress);
	rightMotorJaguar = new CANJaguar(CAN_RightMotorAddress);
	
	// Should rev
	leftJoystick = new SmartJoystick(USB_LeftJoystickPort);
	rightJoystick = new SmartJoystick(USB_RightJoystickPort);
	
	
	
	gyro = new Gyro(ANALOG_GyroPort);
	servo = new Servo(5);
	xAxisAccelerometer = new Accelerometer(ANALOG_XAxisAccelerometerPort);
	yAxisAccelerometer = new Accelerometer(ANALOG_YAxisAccelerometerPort);
	timer = new Timer();

	leftLineSensor = new DigitalInput(DIO_LeftLightSensorPort);
	middleLineSensor = new DigitalInput(DIO_MiddleLightSensorPort);
	rightLineSensor = new DigitalInput(DIO_RightLightSensorPort);
	
	encoders = new Encoders1073(gyro, leftMotorJaguar, rightMotorJaguar);
	encoders->InitEncoders(); // reset and start the encoders
	
	navigation = new Navigation(encoders, xAxisAccelerometer, yAxisAccelerometer, gyro, timer);
	drive = new LNDrive(leftMotorJaguar, rightMotorJaguar, leftJoystick, rightJoystick, navigation, leftEncoder, rightEncoder);
	lineFollower = new LineFollower(drive, leftJoystick, rightJoystick, leftLineSensor, middleLineSensor, rightLineSensor, leftEncoder, rightEncoder);
	minibot = new Minibot();
	dashboardSender = new DashboardSender(driverStation,encoders,leftJoystick,rightJoystick, gyro);
	dashboardReceiver = new DashboardReceiver();
	driverMessages = new DriverMessages(leftJoystick, gyro, encoders);
	cameraManager->StartCamera();
	
	// Launch the background thread....
	InitializeTheZombieZone(this);
	InitializeDashboardReceiverThread(this, dashboardReceiver);
	
	
}


void Robot1073::OperatorControl(void)
{
	encoders->ResetEncoders();
	
	while (IsOperatorControl())
	{
		float pos = leftJoystick->GetZ();
		servo->Set(pos);
		drive->PeriodicService();
		navigation->PeriodicService();
		Wait(WaitTime);				// wait for a motor update time
	}
}



void Robot1073::ZombieZonePeriodicService()
{
		dashboardSender->SendData();
		driverMessages->PeriodicService();
		encoders->PeriodicService();
}

START_ROBOT_CLASS(Robot1073);
