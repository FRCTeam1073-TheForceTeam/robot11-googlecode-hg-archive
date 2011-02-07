//////////////////////////////////////////////////////////
// Filename: SmartJagMotor.cpp
// Author:   John Heden / Ken Cowan
// Date:     Feb 6, 2010
//
// Defines a SmartJagMotor that provides encapsulated Jag motor/encoder functionality
//
//////////////////////////////////////////////////////////
#include "SmartJagMotor.h"



// Need the CAN address of this motor, encoder pulses per ft, and whether motors & encoders are reversed... 
SmartJaguarMotorEncoder::SmartJaguarMotorEncoder(UINT8 deviceNumber, UINT16 _pulsesPerFt, bool reverseMotor, bool reverseEncoder, double changeThreshold) 
: CANJaguar(deviceNumber),								// pass this address to base class constructor
  isMotorReversed(reverseMotor),
  isEncoderReversed(reverseEncoder),
  pulsesPerFt(_pulsesPerFt),
  threshold(changeThreshold)
{
	SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
	ConfigEncoderCodesPerRev(_pulsesPerFt);
	
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
	
	initial_val = GetPositionUnaltered();
}


void
SmartJaguarMotorEncoder::Set(float value)
{
	float new_value = value;
	if(isMotorReversed)	//If motor is reversed, reverse setting
		new_value *= -1.0;
	
	CANJaguar::Set(new_value);
}

double SmartJaguarMotorEncoder::GetPosition()
{
	// Position as read from encoder, via CANJaguar
	double pure_pos = GetPositionUnaltered();

	if(isEncoderReversed)	//If encoder is reversed, reverse value
		pure_pos *= -1.0;
	
	// Position relative to the initial position
	double relative_pos = pure_pos - initial_val;
	
	// Distance the encoder counted
	double delta = relative_pos - last_val;
	
	// If the change is small, use the last saved position.  Assuming
	// it is noise on the cable or something
	if (fabs(delta) < threshold)
		relative_pos = last_val;
	
	// Save the position for the next time we're called
	last_val = relative_pos;
	
	return relative_pos;
}

double SmartJaguarMotorEncoder::GetNetPosition()
{
	double saved_last_val = last_val;
	double pos = GetPosition(); // note that GetPosition() updates last_val;
	double delta = pos - saved_last_val;
	
	return delta;
}

double SmartJaguarMotorEncoder::GetPositionUnaltered()
{
	return this->CANJaguar::GetPosition();
}
