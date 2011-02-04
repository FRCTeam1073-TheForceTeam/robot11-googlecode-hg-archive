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
	static float lastTime = 0;
	static float currentTime;
	
	currentTime = timer->Get();
	//float acceleration = yAxisAccelerometer->GetAcceleration();
	
	heading = gyro->GetAngle();
	heading -= 360 * ((int)(heading / 360));
	
	//velocity += acceleration * (currentTime - lastTime);
	
	//x += velocity * (float)cos(ToRadians(heading));
	//y += velocity * (float)sin(ToRadians(heading));
	
	
	
	lastTime = currentTime;
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
