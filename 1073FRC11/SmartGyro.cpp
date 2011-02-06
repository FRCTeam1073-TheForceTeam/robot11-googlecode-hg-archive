//////////////////////////////////////////////////////////
// Filename: SmartGyro.cpp
// Author:   Ken Cowan
// Date:     Feb 6, 2011
//
// This file contains ...
//
//////////////////////////////////////////////////////////
#include "SmartGyro.h"

float SmartGyro::GetAngle()
{
	float raw_angle = this->Gyro::GetAngle();
	
	//for now, don't mess w/angle
	
	return raw_angle;
}


