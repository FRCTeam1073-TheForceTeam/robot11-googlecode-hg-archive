#ifndef LNDRIVE_H_
#define LNDRIVE_H_

#include "userincludes.h"
#include "Navigation.h"

class LNDrive;

class LNDrive
{
	public:
		
		LNDrive(SpeedController *lmj, SpeedController *rmj, Joystick *lj, Joystick *rj, Navigation *n);
		void PeriodicService();
		
	private:
		
		void TankDrive();
		void Scale();
		void SetMotors();
		
		void StartFollowLine(); 
						// lines: leftStraight, leftFork, rightFork, rightStraight
						// columns: left1, left2, left3, right1, right2, right3
						// rows: top, middle, bottom
						// foot height: topHigh, topLow, middleHigh, middleLow, bottomHigh, bottomLow
						// 
						/* stops at end of line, decide which line to 
						follow depending on start position, which foot
						to attempt, turn towards the target if line is 
						forked */
		bool StatusFollowLine(); // RETURN: boolean (t/f, done/still working)
		void StopFollowLine();
		
		
		Joystick *leftJoystick;
		Joystick *rightJoystick;
		SpeedController *leftMotorJaguar;
		SpeedController *rightMotorJaguar;
		Navigation *navigation;
		
		float left;		// What is left ?????????
		float right;	// what is right ????????
};

#endif
