#ifndef NAVIGATION_H_
#define NAVIGATION_H_

#include "userincludes.h"

class Navigation;

class Navigation
{
	public:
		Navigation(Encoder *le, Encoder *re, Accelerometer *xaccel, Accelerometer *yaccel, Gyro *g, Timer *t);
		float GetX();
		float GetY();
		float GetXVel();
		float GetYVel();
		float GetSX();
		float GetSY();
		float GetHeading();
		void PeriodicService();
		float ToRadians(float degrees);
		float ToDegrees(float radians);
		
	private:
		
		//PositionArmHeight(); (part of object handling)
		/// initiates the robot positioning sequence (and carries through)
		void StartPositionRobotToColumn();
		/// return: boolean, positioned (t) or not (f). 
		bool StatusPositionRobotToColumn();
		/// stop the robot positioning (when held button is let up??)
		void StopPositionRobotToColumn();
		/// x, y, std dev x, std dev y, heading. 
		/// in a vertical orientation of the field, the left corner 
		/// when facing the targets (as intial robot position) is 0,0.
		/// down/right are both positive. units are in feet.
		
		
		Encoder *leftEncoder;
		Encoder *rightEncoder;
		Gyro *gyro;
		Accelerometer *xAxisAccelerometer;
		Accelerometer *yAxisAccelerometer;
		Timer *timer;
		
		float x;
		float y;
		float xVelocity;
		float yVelocity;
		float heading;
};

#endif
