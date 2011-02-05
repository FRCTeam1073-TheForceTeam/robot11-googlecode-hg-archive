#include "Navigation.h"

Navigation::Navigation(Encoders1073 *enc, ADXL345_I2C *accel, Gyro *g, Timer *t)
{
	encoders = enc;
	accelerometer = accel;
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

float Navigation::GetXVelocity()
{
	return xVelocity;
}

float Navigation::GetYVelocity()
{
	return yVelocity;
}

void Navigation::PeriodicService()
{
	static float lastTime = 0;
	static float currentTime;
	
	static float lastXVelocity = 0;
	static float lastYVelocity = 0;
	
	currentTime = timer->Get();
	
	float yAcceleration = accelerometer->GetAcceleration(ADXL345_I2C::kAxis_X) * 32; // 1 g = 32 ft/s^2
	float xAcceleration = accelerometer->GetAcceleration(ADXL345_I2C::kAxis_Y) * 32;
	
	

	xVelocity += xAcceleration * (currentTime - lastTime);
	heading += ((xVelocity - lastXVelocity) / (2 * xAcceleration)) / .5208333 / Pi * 180;

	if (fabs(xVelocity) <= .2)
	{
		heading = gyro->GetAngle();
	}
	
	
	heading = gyro->GetAngle();
	heading -= 360 * ((int)(heading / 360));
	
	if(heading < 0)
	{
		heading = 360 + heading;
	}
	
	yVelocity += yAcceleration * (currentTime - lastTime);
	float distanceTravelled = (yVelocity - lastYVelocity) / (2 * yAcceleration);
	
	x += distanceTravelled * (float)cos(ToRadians(heading + Pi / 2));
	y += distanceTravelled * (float)sin(ToRadians(heading + Pi / 2));
	
	lastTime = currentTime;
	lastXVelocity = xVelocity;
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
