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
	xVelocity = 0;
	yVelocity = 0;
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
	
	static float lastLeftEncoderReading = 0;
	static float currentLeftEncoderReading = 0;
	
	static float lastRightEncoderReading = 0;
	static float currentRightEncoderReading = 0;
	
	static float lastYVelocity = 0;
	
	currentTime = timer->Get();
	currentLeftEncoderReading = leftEncoder->GetDistance();
	currentRightEncoderReading = rightEncoder->GetDistance();
	
	//float yAcceleration = yAxisAccelerometer->GetAcceleration() * 32; // 1 g = 32 ft/s^2
	//float xAcceleration = xAxisAccelerometer->GetAcceleration() * 32;
	
	/*
	if(fabs(xAcceleration) < .10)
	{
		xVelocity += xAcceleration * (currentTime - lastTime);
		heading += xVelocity * (currentTime - lastTime);
	}
	else
	{
		xVelocity = 0;
		heading = gyro->GetAngle();
	}
	*/
	
	heading = gyro->GetAngle();
	heading -= 360 * ((int)(heading / 360));
	
	if(heading < 0)
	{
		heading = 360 + heading;
	}
	
	//yVelocity += yAcceleration * (currentTime - lastTime);
	//float distanceTravelled = (yVelocity - lastYVelocity) / (2 * yAcceleration)
	
	//x += distanceTravelled * (float)cos(ToRadians(heading));
	//y += distanceTravelled * (float)sin(ToRadians(heading));
	
	lastTime = currentTime;
	lastLeftEncoderReading = currentLeftEncoderReading;
	lastRightEncoderReading = currentRightEncoderReading;
	lastYVelocity = yVelocity;
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
