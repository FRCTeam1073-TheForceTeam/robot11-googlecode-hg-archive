//////////////////////////////////////////////////////////
// Filename: SmartGyro.h
// Author:   Ken Cowan
// Date:     Feb 6, 2011
//
// This file contains a Gyro subclass that tries to eliminate noise from bad cables,
// and rounds the heading to be 0 to 360
//
//////////////////////////////////////////////////////////
#ifndef SmartGyro_H_
#define SmartGyro_H_

#include "userincludes.h"

class SmartGyro;

static const float kDefaultGyroNoiseThreshold = 0.3;  // is less than 3/10 of a degree, ignore it

class SmartGyro : public Gyro
{
protected:
	float initial_angle;	// in case the Gyro does not start at 0
	float last_angle;		// last angle returned.  Used in "net" calculation
	
	float threshold;		// if the difference in the angle is less than this, ignore the "bounce"

	
public:
	SmartGyro( UINT32 port, float noiseThreshold = kDefaultGyroNoiseThreshold );   // constructor like Gyro

	// Return the current angle of the gyro, in degrees.  Attempts to keep result steady by
	// ignoring minor bounce in the angle
	virtual float GetAngle();
	
	// Current angle of the gyro in radians
	float GetAngleRadians();
	
	// Return the raw angle, useful for diagnostics
	float GetAngleUnaltered();
	
	// Return the change sicne the last call to GetAngle
	float GetNetAngle();
	
	void Reset();
};

#endif
