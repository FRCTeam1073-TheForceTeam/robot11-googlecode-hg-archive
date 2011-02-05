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
	pincerJaguar = new CANJaguar(CAN_PincerMotorAddress);
	armJaguar = new CANJaguar(CAN_ElevatorArmMotorAddress);
	
	// Should rev
	leftJoystick = new SmartJoystick(USB_LeftJoystickPort);
	rightJoystick = new SmartJoystick(USB_RightJoystickPort);
	
	
	
	gyro = new Gyro(ANALOG_GyroPort);
	servo = new Servo(5);
	accelerometer = new ADXL345_I2C(DIO_XAxisAccelerometerPort);
	timer = new Timer();

	leftLineSensor = new DigitalInput(DIO_LeftLightSensorPort);
	middleLineSensor = new DigitalInput(DIO_MiddleLightSensorPort);
	rightLineSensor = new DigitalInput(DIO_RightLightSensorPort);
	
	encoders = new Encoders1073(gyro, leftMotorJaguar, rightMotorJaguar);
	
	navigation = new Navigation(encoders, accelerometer, gyro, timer);
	drive = new LNDrive(leftMotorJaguar, rightMotorJaguar, leftJoystick, rightJoystick, navigation, encoders);
	lineFollower = new LineFollower(drive, leftJoystick, rightJoystick, leftLineSensor, middleLineSensor, rightLineSensor, encoders);
	minibot = new Minibot();
	dashboardSender = new DashboardSender(driverStation,encoders,leftJoystick,rightJoystick, gyro);
	dashboardReceiver = new DashboardReceiver();
	driverMessages = new DriverMessages(leftJoystick, gyro, encoders, navigation);
	cameraManager->StartCamera();
	
	// Launch the background thread....
	InitializeTheZombieZone(this);
	InitializeDashboardReceiverThread(this, dashboardReceiver);
	
	
}

void Robot1073::OperatorControl(void)
{
	float last_servo_pos = 0;
	encoders->ResetEncoders();
	
	while (IsOperatorControl() && IsEnabled() )
	{
		// If the joystick is different than the last time, update
		// the servo position
		float pos = leftJoystick->GetZ();
		if (pos != last_servo_pos)
		{
			servo->Set(pos);
			last_servo_pos = pos;
		}
		
		drive->PeriodicService();
		navigation->PeriodicService();
		//lineFollower->PeriodicService();
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
