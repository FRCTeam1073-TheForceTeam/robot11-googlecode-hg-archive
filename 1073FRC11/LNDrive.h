#ifndef LNDRIVE_H_
#define LNDRIVE_H_

#include "userincludes.h"
#include "SmartJoystick.h"
#include "SmartJagMotor.h"
#include "Navigation.h"


class LNDrive;
class Encoders1073;

class LNDrive
{
	public:
		
		LNDrive(SmartJaguarMotorEncoder *lmj, SmartJaguarMotorEncoder *rmj, SmartJoystick *lj, SmartJoystick *rj, Navigation *n, Encoders1073 *encoders);
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
		
		
		
		SmartJoystick *leftJoystick;
		SmartJoystick *rightJoystick;
		SmartJaguarMotorEncoder *leftMotorJaguar;
		SmartJaguarMotorEncoder *rightMotorJaguar;
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
