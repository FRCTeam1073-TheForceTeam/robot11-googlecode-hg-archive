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
		
		float left;
		float right;
		float desiredAngle;
		float currentAngle;
		
		bool overridden;
		bool turningToAngle;
		bool isTankDrive;
};

#endif
