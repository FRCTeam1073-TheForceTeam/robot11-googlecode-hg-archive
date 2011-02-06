//////////////////////////////////////////////////////////
// Filename: SmartJagMotor.cpp
// Author:   
// Date:     Feb 6, 2010
//
// Defines a SmartJagMotor that provides encapsulated Jag motor/encoder functionality
//
//////////////////////////////////////////////////////////
#include <stdio.h>
#include "WPILib.h"
#include "SmartJagMotor.h"



// Need the CAN address of this motor, encoder pulses per ft, and whether motors & encoders are reversed... 
SmartJaguarMotorEncoder::SmartJaguarMotorEncoder(int canAddress, int pulsesPerFt, bool reverseMotor, bool reverseEncoder) 
: CANJaguar(canAddress),								// pass this address to base class constructor
  isMotorReversed(reverseMotor),
  isEncoderReversed(reverseEncoder)
{
	SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
	ConfigEncoderCodesPerRev(pulsesPerFt);
	
	ResetEncoder();
}



void 
SmartJaguarMotorEncoder::ResetEncoder()
{
	CANJaguar::ControlMode oldMode = GetControlMode();
	ChangeControlMode(CANJaguar::kPosition);
	DisableControl();
	EnableControl(0.0);
	ChangeControlMode(oldMode);
}


void
SmartJaguarMotorEncoder::Set(float value)
{
	if(isMotorReversed)	//If motor is reversed, reverse setting
		value *= -1.0;	
	CANJaguar::Set(value);
}

double
SmartJaguarMotorEncoder::GetPosition()
{
	double pos = CANJaguar::GetPosition();
	
	if(isEncoderReversed)	//If encoder is reversed, reverse value
		pos *= -1.0;	
	return pos;
}

