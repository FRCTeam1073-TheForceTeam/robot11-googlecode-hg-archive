#ifndef USERINCLUDES_H_
#define USERINCLUDES_H_

#include "WPILib.h"
#include "Math.h"
#include <list>
#include <map>
#include <string>
#include <time.h>

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

enum {RELAY_PORT_1 = 1,
	  RELAY_PORT_2,
	  RELAY_PORT_3,
	  RELAY_PORT_4,
	  RELAY_PORT_5,
	  RELAY_PORT_6};


// CAN Address Assignments

	// Total of 6 Jaguars used/defined as follows,,,

	// Two Jaguars for Left & Right Drive motors
	const unsigned int CAN_LeftMotorAddress = 3;
	// JAGIO --> Left Encoder connected to Left Motor Jaguar..
	const unsigned int CAN_RightMotorAddress = 2;
	// JAGIO --> Right Encoder connected to Left Motor Jaguar..

	// Two Jaguars driving 2 separate Elevator motors
	const unsigned int CAN_ElevatorUpDownAMotorAddress = 4; 
	const unsigned int CAN_ElevatorUpDownBMotorAddress = 5;
	// JAGIO --> Elevator 'Down'limit Switch connected to BOTH Elevator A & B limits in series
	// JAGIOIO --> Elevator Optical Encoder connected to JaguarUpDownA Encoder Input
	
	// More Jaguars for Pincer
	const unsigned int CAN_PincerMotorAddress = 6;
	
	// Analog -> Pincer Mag encoder defined below in Analog input section
	
	//Another Jaguar for Arm rotate.
	const unsigned int CAN_ElevatorArmMotorAddress = 7;
	// JAGIO --> Down limit switch for Elevator Arm to jaguar limit switch
	// ElevatorArm Mag encoder defined below in Analog input seaction
	

// PWMs defined for two servos (two PWMs used total)
	static const int PWM_CameraTiltServoPort = PWM_PORT_5;   // Questionable usage ?  
	static const int PWM_ElevatorBrakeServo = PWM_PORT_6; 	 // Servo used to stop the elevator movement


//Digital I/O Ports (5 total)
	static const int DIO_LeftLightSensorPort = 	 DIGITAL_PORT_1;
	static const int DIO_MiddleLightSensorPort = DIGITAL_PORT_2;
	static const int DIO_RightLightSensorPort =  DIGITAL_PORT_3;
	
//I2C Slot
	static const int IO_Slot = 4;
	
	// Relay inputs for 4 spikes 
	static const int RELAY_MinibotDeployer = 	RELAY_PORT_1;	// Spike 1 -> For/Rev/Off
	static const int RELAY_MinibotPositioner = RELAY_PORT_2;	
	static const int RELAY_PincerRoller = 	  RELAY_PORT_3;		// Spike 3 -> For/Rev/Off
	static const int RELAY_RetroIlluminator = RELAY_PORT_4;	// Spike 4 -> For/Off = light On/off
	
	//various Analog Port defines (5 total)
	static const int ANALOG_GyroPort = ANALOG_PORT_1; //Gyro can ONLY be placed on Port 1
	static const int ANALOG_PincerMagneticEncoder = ANALOG_PORT_2;
	static const int ANALOG_ElevatorArmMagneticEncoder = ANALOG_PORT_3;
	
	//PWM ports in use	
	static const int PWM_ChasisCamera = PWM_PORT_5;
	
	// Digital I/O ports in use
	static const int DIO_ElevatorUpDownEncoderAPort = DIGITAL_PORT_10;
	static const int DIO_ElevatorUpDownEncoderBPort = DIGITAL_PORT_11;
	
	
	// Let's define  orientation  motors & encoders...
	// Motor orientation for BOTH CAN and PWM Jaguars
	static const bool IsLeftMotorReversed = true;
	static const bool IsRightMotorReversed = false;

	static const bool IsLeftEncoderReversed = false;
	static const bool IsRightEncoderReversed = true;
	
	
//USB Ports
	
	static const int USB_LeftJoystickPort = 1;
	static const int USB_RightJoystickPort = 2;
	static const int USB_OperatorJoystickPort = 3;
	
//Joystick Buttons
	
	//Left Joystick
	
	static const int LeftTurboButton = 1;
	static const int TurnToRackButton = 2;
	static const int CycleDriverStationDiagsButton = 6;
	static const int SwitchDriveModeButton = 10;
	
	//Right Joystick

	static const int RightTurboButton = 1;
	static const int LineFollowButton = 2;
	
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
	
	static const int ElevatorNextPositionTestButton = 3;
	
//Other Useful(?) Constants
	static const float WaitTime = .05;
	static const float Pi = 3.14159;
	static const float WheelCircumferenceFeet = (6.25/12 * Pi);  // 6.25 inches
	static const float PulsesPerFoot = 660; // exact
	static const float AngleStraightHome = 0;
	static const float AngleStraightAway = 180;
	static const UINT16 ElevatorPulsesPerFoot = 200;
	
	static const UINT16 DriveWheelPulsesPerFoot = 600; // found through experimentation
	

#define sizeof_array(ARRAY) (sizeof(ARRAY)/sizeof(ARRAY[0])) 
	

#endif
