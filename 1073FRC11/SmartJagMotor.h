//////////////////////////////////////////////////////////
// Filename: SmartJaguarMotorEncoder
// Author:   
// Date:     January 23, 2011
//
// Description: This file contains the SmartJaguarMotoeEncode Class to deal with the nuances of the Jag
//////////////////////////////////////////////////////////
#ifndef __SmartJaguarMotor_h__
#define __SmartJaguarMotor_h__

#include "WPILib.h"
#include "Vision\AxisCamera.h"


class SmartJaguarMotorEncoder : public CANJaguar
{
public: 
	// Need the CAN address of this motor & pulses per ft, 
	SmartJaguarMotorEncoder(int canAddress, int PulsesPerFt = 0, bool reverseMotor = false, bool reverseEncoder = false);	
	void Set(float value);
	
	// Encoder functions
	void ResetEncoder();
	double GetPosition();

private: 
	bool isMotorReversed;
	bool isEncoderReversed;								
};




#endif

