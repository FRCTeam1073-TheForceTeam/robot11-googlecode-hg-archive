#ifndef USERINCLUDES_H_
#define USERINCLUDES_H_

#include "WPILib.h"
#include "Math.h"
#include <list>
#include <map>
#include <string>

enum {PWM_PORT_1 = 1,
	  PWM_PORT_2,
	  PWM_PORT_3,
	  PWM_PORT_4,
	  PWM_PORT_5,
	  PWM_PORT_6,
	  PWM_PORT_7,
	  PWM_PORT_8};

enum {DIGITAL_PORT_1 = 1,
	  DIGITAL_PORT_2,
	  DIGITAL_PORT_3,
	  DIGITAL_PORT_4,
	  DIGITAL_PORT_5,
	  DIGITAL_PORT_6,
	  DIGITAL_PORT_7,
	  DIGITAL_PORT_8,
	  DIGITAL_PORT_9,
	  DIGITAL_PORT_10,
	  DIGITAL_PORT_11,
	  DIGITAL_PORT_12,
	  DIGITAL_PORT_13,
	  DIGITAL_PORT_14};

enum {ANALOG_PORT_1 = 1,
	  ANALOG_PORT_2,
	  ANALOG_PORT_3,
	  ANALOG_PORT_4,
	  ANALOG_PORT_5,
	  ANALOG_PORT_6,
	  ANALOG_PORT_7,
	  ANALOG_PORT_8};

// CAN Address Assignments
#define USE_CAN_JAGUARS true
	const unsigned int CAN_LeftMotorAddress = 2; 
	const unsigned int CAN_RightMotorAddress = 3; 

	static const int PWM_LeftMotorPort = PWM_PORT_1; 
	static const int PWM_RightMotorPort = PWM_PORT_2;
	static const int PWM_CameraTiltServoPort = PWM_PORT_5;

	// Motor orientation for BOTH CAN and PWM Jaguars
	static const bool IsLeftMotorReversed = true;
	static const bool IsRightMotorReversed = false;

//Digital Ports
	
	static const int DIO_LeftLightSensorPort = DIGITAL_PORT_1;
	static const int DIO_MiddleLightSensorPort = DIGITAL_PORT_2;
	static const int DIO_RightLightSensorPort = DIGITAL_PORT_3;
	static const int DIO_LeftEncoderAPort = DIGITAL_PORT_5;
	static const int DIO_LeftEncoderBPort = DIGITAL_PORT_6;
	static const int DIO_RightEncoderAPort = DIGITAL_PORT_8;
	static const int DIO_RightEncoderBPort = DIGITAL_PORT_9;
	//static const int DIO_LeftDrivetrainJaguar = DIGITAL_PORT_13;
	
	// Let's define  orientation of both encoders...
	static const bool IsLeftEncoderReversed = true;
	static const bool IsRightEncoderReversed = false;
	
//Analog Ports

	static const int ANALOG_GyroPort = ANALOG_PORT_1; //Gyro can ONLY be placed on Port 1
	static const int ANALOG_XAxisAccelerometerPort = ANALOG_PORT_2;
	static const int ANALOG_YAxisAccelerometerPort = ANALOG_PORT_3;
	
//USB Ports
	
	static const int USB_LeftJoystickPort = 1;
	static const int USB_RightJoystickPort = 2;
	static const int USB_OperatorJoystickPort = 3;
	
//Joystick Buttons
	
	//Have to add a turbo mode: When both trigger buttons on left+right joystick are pressed,
	//the robot will go full forwards and backwards
	
	//Left Joystick
	
	static const int TurnToRackButton = 2;
	
	//Right Joystick
	
		
	
	//Operator Joystick
	
	static const int GripGrabButton = 12;
	static const int GripReleaseButton = 11;
	//static const int SetHeightLowButton = 3;
	//static const int SetHeightMediumButton = 4;   //More detail to be added later, probably won't be on opjoystick
	//static const int SetHeightHighButton = 5;
	static const int MinibotDeployButton = 7;
	//elevator handled by joystick
	static const int GripRollerUpButton = 5;
	static const int GripRollerDownButton = 3;
	static const int GripTiltUpButton = 10;
	static const int GripTiltDownButton = 9;
	static const int ArmUpButton = 6;
	static const int ArmDownButton = 4;
	static const int CameraSwitchButton = 2;	
	
//Other Useful(?) Constants
	static const float WaitTime = .05;
	static const float Pi = 3.14159; 
	static const float WheelCircumference = .5 * Pi;
	static const float PulsesPerFoot = 962; //Inexact, talk to mechanical later
	static const float AngleStraightHome = 0;
	static const float AngleStraightAway = 180;

#endif
