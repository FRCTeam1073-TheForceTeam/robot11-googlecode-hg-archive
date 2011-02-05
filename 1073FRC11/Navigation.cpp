#include "Navigation.h"

Navigation::Navigation(Encoders1073 *enc, Accelerometer *xaccel, Accelerometer *yaccel, Gyro *g, Timer *t)
{
	encoders = enc;
	yAxisAccelerometer = yaccel;
	gyro = g;
	timer = t;
	
	//temporary (will be set properly in StartPositionRobotToColumn) 
	x = 0;
	y = 0;
	xvel=0;
	yvel=0;
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
	float ang = ToRadians(gyro->GetAngle());
#if 0
	float _y = yAxisAccelerometer->GetAcceleration();
	float _x= xAxisAccelerometer->GetAcceleration();
	
	
	float yaccel=_y*sin(ang)-_x*cos(ang);
	float xaccel=_x*sin(ang)+_y*cos(ang);
	xvel+=xaccel*WaitTime;
	yvel+=yaccel*WaitTime;
#else
	//this is the encoder rotating stuff
	//COMMENTED OUT TEMPORARILY
	//"GetVelocity" is not stated yet
	//float lvel = leftEncoder->GetVelocity();
	//float rvel = rightEncoder->GetVelocity();
	//float avgvel=(rvel+lvel)/2;
	//float xvel = avgvel*sin(ang);
	//float yvel = avgvel*cos(ang);
#endif
	
	
	x+=xvel*WaitTime;
	y+=yvel*WaitTime;
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
