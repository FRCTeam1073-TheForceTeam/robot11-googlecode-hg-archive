#ifndef USERINCLUDES_H_
#define USERINCLUDES_H_

#include "WPILib.h"
#include "Math.h"

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
	  DIGITAL_PORT_13};

enum {ANALOG_PORT_1 = 1,
	  ANALOG_PORT_2,
	  ANALOG_PORT_3,
	  ANALOG_PORT_4,
	  ANALOG_PORT_5,
	  ANALOG_PORT_6,
	  ANALOG_PORT_7,
	  ANALOG_PORT_8};

// CAN Address Assignments
#define USE_CAN_JAGUARS false
	const unsigned int CAN_LeftMotorAddress = 1; 
	const unsigned int CAN_RightMotorAddress = 2; 


//PWM Ports
	static const int PWM_LeftMotorPort = PWM_PORT_1; 
	static const int PWM_RightMotorPort = PWM_PORT_2; 
	static const int PWM_CameraTiltServoPort = PWM_PORT_5;

	// Motor orientation for BOTH CAN and PWM Jaguars
	static const bool IsLeftMotorReversed = true;
	static const bool IsRightMotorReversed = false;


//Digital Ports
	// The following are the left/right 90 line optical encoders supporting line 360 counts/revolution (quadriture) 
	static const int DIO_LeftEncoderAPort = DIGITAL_PORT_5;
	static const int DIO_LeftEncoderBPort = DIGITAL_PORT_6;
	static const int DIO_RightEncoderAPort = DIGITAL_PORT_8;
	static const int DIO_RightEncoderBPort = DIGITAL_PORT_9;

	// Let's define  orientation of both encoders...
	static const bool IsLeftEncoderReversed = true;
	static const bool IsRightEncoderReversed = false;
	
	// Various Line sensorr definitions...
	static const int  DIO_LeftLineSensorPort = DIGITAL_PORT_1;
	static const int  DIO_CenterLineSensorPort = DIGITAL_PORT_2;
	static const int  DIO_RightLineSensorPort = DIGITAL_PORT_3;
	

//Analog Ports
	static const int ANALOG_GyroPort = ANALOG_PORT_1;   // GYRO CAN ONLY BE PLACED ON Analog Port 1
	static const int ANALOG_XAxisAccerometerPort = ANALOG_PORT_2;   // X Axis ccelerometer
	static const int ANALOG_YAxisAccerometerPort = ANALOG_PORT_3;   // Y Axis Accelerometer


//Driver Station Ports
	const int USB_LeftJoyStickPort = 1;
	const int USB_RightJoyStickPort = 2;
	const int USB_OperatorJoyStickPort = 3;
	
	
#endif
