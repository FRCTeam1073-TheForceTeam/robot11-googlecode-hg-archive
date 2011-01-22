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
	  DIGITAL_PORT_8};

enum {ANALOG_PORT_1 = 1,
	  ANALOG_PORT_2,
	  ANALOG_PORT_3,
	  ANALOG_PORT_4,
	  ANALOG_PORT_5,
	  ANALOG_PORT_6,
	  ANALOG_PORT_7,
	  ANALOG_PORT_8};

//PWM Ports

	static const int PWM_LeftMotorPort = PWM_PORT_1; 
	static const int PWM_RightMotorPort = PWM_PORT_2; 

//Digital Ports
	
	static const int DIO_LeftJoystickPort = DIGITAL_PORT_1;
	static const int DIO_RightJoystickPort = DIGITAL_PORT_2;
	static const int DIO_LeftEncoderAPort = DIGITAL_PORT_3;
	static const int DIO_LeftEncoderBPort = DIGITAL_PORT_4;
	static const int DIO_RightEncoderAPort = DIGITAL_PORT_5;
	static const int DIO_RightEncoderBPort = DIGITAL_PORT_6;
	static const int DIO_AccelerometerPort = DIGITAL_PORT_7;

//Analog Ports

	static const int ANALOG_GyroPort = ANALOG_PORT_1;

#endif
