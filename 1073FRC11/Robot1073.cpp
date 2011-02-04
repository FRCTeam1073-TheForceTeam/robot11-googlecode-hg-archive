//////////////////////////////////////////////////////////
// Filename: Robot1073.cpp
// Author:   
// Date:     January 23, 2011
//
// Description: This file contains the main defintion for the Team1073 Robot.
//
//////////////////////////////////////////////////////////
#include "Robot1073.h"

void Robot1073::ResetEncoders()
{
	leftEncoder->Reset();
	rightEncoder->Reset();		
}
void Robot1073::InitEncoders()
{
	ResetEncoders();

	// Wheel is .5 foot diameter.  We found by experimenting 962 pulses per rotation of wheel
	leftEncoder->SetDistancePerPulse(.5 * 3.1415926535 / 962);
	rightEncoder->SetDistancePerPulse(.5 * 3.1415926535 / 962);
	leftEncoder->Start();
	rightEncoder->Start();	
}

Robot1073::Robot1073(void)
: camera (AxisCamera::GetInstance())					// This initialization syntax necessary because of the referance associated with GetInstance().

{
	cameraManager = new CameraManager();
	driverStation = DriverStation::GetInstance();

	
// Both the PWM & CAN Jaguars are suportable with this simple comple time option...	
#if !USE_CAN_JAGUARS
	leftMotorJaguar = new Jaguar(PWM_LeftMotorPort);
	rightMotorJaguar = new Jaguar(PWM_RightMotorPort);
#else
	leftMotorJaguar = new CANJaguar(CAN_LeftMotorAddress);
	rightMotorJaguar = new CANJaguar(CAN_RightMotorAddress);
#endif
	
	// Should rev
	leftJoystick = new Joystick(USB_LeftJoystickPort);
	rightJoystick = new Joystick(USB_RightJoystickPort);
	
	leftEncoder = new Encoder(DIO_LeftEncoderAPort, DIO_LeftEncoderBPort, IsLeftEncoderReversed);
	rightEncoder = new Encoder(DIO_RightEncoderAPort, DIO_RightEncoderBPort, IsRightEncoderReversed);
	
	
	InitEncoders(); // reset and start the encoders
	
	gyro = new Gyro(ANALOG_GyroPort);
	xAxisAccelerometer = new Accelerometer(ANALOG_XAxisAccelerometerPort);
	yAxisAccelerometer = new Accelerometer(ANALOG_YAxisAccelerometerPort);
	timer = new Timer();
	
	navigation = new Navigation(leftEncoder, rightEncoder, xAxisAccelerometer, yAxisAccelerometer, gyro, timer);
	drive = new LNDrive(leftMotorJaguar, rightMotorJaguar, leftJoystick, rightJoystick, navigation);
	minibot = new Minibot();
	dashboardSender = new DashboardSender(driverStation,leftEncoder,rightEncoder,leftJoystick,rightJoystick, gyro);
	dashboardReceiver = new DashboardReceiver();
	driverMessages = new DriverMessages(leftJoystick, gyro, leftEncoder, rightEncoder);
	cameraManager->StartCamera();
	
	// Launch the background thread....
	InitializeTheZombieZone(this);
	InitializeDashboardReceiverThread(this, dashboardReceiver);
	
	
}

void Robot1073::Autonomous(void)
{
	ResetEncoders();
	
	// Some code goes here ?  
	// Go & follow Line ?
}

void Robot1073::OperatorControl(void)
{
	ResetEncoders();
	
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





