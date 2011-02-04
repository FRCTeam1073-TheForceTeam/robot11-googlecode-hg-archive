#include "Navigation.h"

Navigation::Navigation(Encoder *le, Encoder *re, Accelerometer *xaccel, Accelerometer *yaccel, Gyro *g, Timer *t)
{
	leftEncoder = le;
	rightEncoder = re;
	yAxisAccelerometer = yaccel;
	gyro = g;
	timer = t;
	
	//temporary (will be set properly in StartPositionRobotToColumn) 
	x = 0;
	y = 0;
	heading = 0;
	velocity = 0;
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
	float _x = xAxisAccelerometer->GetAcceleration();
	float _y = yAxisAccelerometer->GetAcceleration();
	float ang = gyro->GetAngle();
	
	float yaccel=_y*cos(ang)-_x*sin(ang);
	float xaccel=_x*cos(ang)+_y*sin(ang);
	xvel+=xaccel*WaitTime;
	yvel+=yaccel*WaitTime;
}

float Navigation::ToRadians(float degrees)
{
	return degrees *Pi / 180;
}

float Navigation::ToDegrees(float radians)
{
	return radians * 180 / Pi;
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
