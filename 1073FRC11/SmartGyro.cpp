//////////////////////////////////////////////////////////
// Filename: SmartGyro.cpp
// Author:   Ken Cowan
// Date:     Feb 6, 2011
//
// This file contains ...
//
//////////////////////////////////////////////////////////
#include "SmartGyro.h"

static const double PI = 2*acos(0.0);

float mod360(float lhs) 
{
	float angle = lhs;
	
	if (angle < 0.0f)
		angle += 360.0;
		
	if (angle > 360.0f)
		return angle - int(angle/360.0f) * 360.0f;
	else
		return angle;
}

SmartGyro::SmartGyro(UINT32 port, float noiseThreshold) : Gyro(port), threshold(noiseThreshold)
{
	Reset();
	last_angle = initial_angle;
}


float SmartGyro::GetAngle()
{
	float raw_angle = GetAngleUnaltered();
	
	// If the gyro moved more than our threshold amount,
	// update the last angle and return the new one
	if (fabs(raw_angle - last_angle) >= threshold )	
	{
		last_angle = mod360(raw_angle);
		return last_angle;
	}
	
	return mod360(last_angle - initial_angle);
	
}

float SmartGyro::GetAngleUnaltered()
{
	float raw_angle = this->Gyro::GetAngle();	
	return raw_angle;
}

float SmartGyro::GetAngleRadians()
{
	float angle_degrees = GetAngle();
	float angle_radians = angle_degrees / (PI / 180);
	
	return angle_radians;			
}

void SmartGyro::Reset()
{
	Gyro::Reset();
	initial_angle = GetAngleUnaltered();
}
