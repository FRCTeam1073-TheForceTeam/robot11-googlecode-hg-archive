#ifndef LNDRIVE_H_
#define LNDRIVE_H_

#include "userincludes.h"
#include "Navigation.h"

class LNDrive;

class LNDrive
{
	public:
		
		LNDrive(SpeedController *lmj, SpeedController *rmj, Joystick *lj, Joystick *rj, Navigation *n, Encoders1073 *encoders);
		void PeriodicService();
		
		void Override(float leftMotor, float rightMotor);
		void StopOverride();
		
		void StartTurnToAngle(float angle);
		bool StatusTurnToAngle();
		void StopTurnToAngle();
		
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
	private:
		
		void TankDrive();
		void ArcadeDrive();
		void Scale();
		void SetMotors();
		void UpdateTurnToAngle();
		void CheckDriveMode();
		
		
		
		Joystick *leftJoystick;
		Joystick *rightJoystick;
		SpeedController *leftMotorJaguar;
		SpeedController *rightMotorJaguar;
		Navigation *navigation;
		Encoders1073 *encoders;
		
		float left;		// What is left ?????????
		float right;	// what is right ????????
		float desiredAngle;
		float currentAngle;
		
		bool overridden;
		bool turningToAngle;
		bool isTankDrive;
};

#endif
