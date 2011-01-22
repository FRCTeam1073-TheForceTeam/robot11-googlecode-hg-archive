#include "Navigation.h"

Navigation::Navigation(Encoder *le, Encoder *re, Accelerometer *a, Gyro *g)
{
	leftEncoder = le;
	rightEncoder = re;
	accel = a;
	gyro = g;
	
	//temporary (will be set properly in StartPositionRobotToColumn) 
	x = 0;
	y = 0;
	heading = 0;
}
		
float Navigation::GetX()
{
	return x;
}
float Navigation::GetY()
{
	return y;
}

float Navigation::GetHeading()
{
	return heading;
}

void Navigation::PeriodicService()
{
	
}

void Navigation::StartPositionRobotToColumn()
{
	
}

bool Navigation::StatusPositionRobotToColumn()
{
	return false;
}

void Navigation::StopPositionRobotToColumn()
{
	
}
