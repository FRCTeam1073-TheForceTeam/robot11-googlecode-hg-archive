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

class SmartGyro : public Gyro
{
protected:
	float last_angle;

public:
	SmartGyro( UINT32 port ) : Gyro(port) {};  // constructor like Gyro
	virtual float GetAngle();
};

#endif
