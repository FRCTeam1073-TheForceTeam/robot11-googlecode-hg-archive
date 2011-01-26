// FRC 11 Season

#include "Robot1073.h"

Robot1073::Robot1073(void)
{
	leftMotorJaguar = new Jaguar(PWM_LeftMotorPort);
	rightMotorJaguar = new Jaguar(PWM_RightMotorPort);
	
	leftJoystick = new Joystick(DIO_LeftJoystickPort);
	rightJoystick = new Joystick(DIO_RightJoystickPort);
	
	leftEncoder = new Encoder(DIO_LeftEncoderAPort, DIO_LeftEncoderBPort);
	rightEncoder = new Encoder(DIO_RightEncoderAPort, DIO_RightEncoderBPort);
	
	accel = new Accelerometer(DIO_AccelerometerPort);
	gyro = new Gyro(ANALOG_GyroPort);
	
	navigation = new Navigation(leftEncoder, rightEncoder, accel, gyro);
	drive = new LNDrive(leftMotorJaguar, rightMotorJaguar, leftJoystick, rightJoystick, navigation);
	minibot = new Minibot();
	dashboardSender = new DashboardSender();
}

void Robot1073::Autonomous(void)
{
	
}

void Robot1073::OperatorControl(void)
{
	
	while (IsOperatorControl())
	{
		drive->PeriodicService();
		Wait(0.005);				// wait for a motor update time
	}
}
