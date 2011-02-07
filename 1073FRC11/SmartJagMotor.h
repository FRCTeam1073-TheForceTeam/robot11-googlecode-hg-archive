//////////////////////////////////////////////////////////
// Filename: SmartJaguarMotorEncoder
// Author:   
// Date:     January 23, 2011
//
// Description: This file contains the SmartJaguarMotoeEncode Class to deal with the nuances of the Jag
//////////////////////////////////////////////////////////
#ifndef __SmartJaguarMotor_h__
#define __SmartJaguarMotor_h__

#include "userincludes.h"

static const double kDefaultThreshold = 0.01;

class SmartJaguarMotorEncoder : public CANJaguar
{
public: 
	// Need the CAN address of this motor & pulses per ft, 
	SmartJaguarMotorEncoder(UINT8 deviceNumber, UINT16 _PulsesPerFt = 0, bool reverseMotor = false, bool reverseEncoder = false, double changeThreshold = kDefaultThreshold);	
	void Set(float value);
	
	// Reset the encoder to 0
	void ResetEncoder();	
	
	// Return the position, where noise has been removed
	double GetPosition();
	
	// Return the distance the encoder has moved since the last call
	double GetNetPosition();
	
	// Return the raw position data.  Useful to diagnose bad cables etc.
	double GetPositionUnaltered();
	
	// Use this to display debugging messages
	UINT16 GetPulsePerFt() { return pulsesPerFt; }
	
private: 
	bool isMotorReversed;
	bool isEncoderReversed;	
	
	UINT16 pulsesPerFt;		// scaling factor for the encoder attached to this Jaguar		
	
	double initial_val;		// initial value for the encoder, 0 if it reset properly
	double last_val;		// last recorded value for encoder
	double threshold;  		// if the encoder moves less that this, ignore the motion
};




#endif

