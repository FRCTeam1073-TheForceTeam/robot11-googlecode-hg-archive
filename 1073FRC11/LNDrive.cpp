#include "LNDrive.h"

LNDrive::LNDrive(SpeedController *lmj, SpeedController *rmj, Joystick *lj, Joystick *rj, Navigation *n)
{
	leftJoystick = lj;
	rightJoystick = rj;
	leftMotorJaguar = lmj;
	rightMotorJaguar = rmj;
	navigation = n;
	
	left = 0;
	right = 0;
	
	overridden = false;
	turningToAngle = false;
}

void LNDrive::PeriodicService()
{
	if (leftJoystick->GetRawButton(TurnToRackButton))
	{
		StartTurnToAngle(AngleStraightHome);
	}
	else
	{
		StopTurnToAngle();
	}
	
	if (overridden)
	{
		//Do nothing
	}
	else if (turningToAngle)
	{
		UpdateTurnToAngle();
	}
	else
	{
		TankDrive();
	}
}

void LNDrive::TankDrive()
{
	left = leftJoystick->GetY();
	right = rightJoystick->GetY();

	if(fabs(left) < .1)
	{
		left = 0;
	}
	
	if(fabs(right) < .1)
	{
		right = 0;
	}
	
	Scale();
	SetMotors();
}

void LNDrive::ArcadeDrive()
{
	float x = rightJoystick->GetX();
	float y = leftJoystick->GetY();
	
	left = y - x;
	right = y + x;
	
	Scale();
	SetMotors();
}

void LNDrive::Scale()
{
	if(left > 1)
	{
		left = 1;
		right /= left;
	}
	else if (left < -1)
	{
		left = -1;
		right /= -left;
	}
	
	if(right > 1)
	{
		right = 1;
		left /= right;
	}
	else if (right < -1)
	{
		right = -1;
		left /= -right;
	}
}

void LNDrive::SetMotors()
{
	// Set the left & right motor outputs, reversing if necessary...
	leftMotorJaguar->Set(IsLeftMotorReversed ? -left : left);			
	rightMotorJaguar->Set(IsRightMotorReversed ? -right : right);
	//printf("%f %f\n", left, right);
}

void LNDrive::StartTurnToAngle(float angle)
{
	desiredAngle = angle;
	turningToAngle = true;
}

bool LNDrive::StatusTurnToAngle()
{
	return fabs(desiredAngle - currentAngle) < 2;
}

void LNDrive::StopTurnToAngle()
{
	turningToAngle = false;
}

void LNDrive::UpdateTurnToAngle()
{	
	currentAngle = navigation->GetHeading();
	
	float angleDif = desiredAngle - currentAngle;
	
	if(fabs(angleDif) < 2)
	{
		left = 0;
		right = 0;
	}
	else if (angleDif > 0 && angleDif > 180 ||
			 angleDif < 0 && angleDif < 180)
	{
		left = angleDif / 180;
		right = -angleDif / 180;
	}
	else
	{
		left = -angleDif / 180;
		right = angleDif / 180;
	}
	
	Scale();
	SetMotors();
}

void LNDrive::Override(float leftMotor, float rightMotor)
{
	overridden = true;
	
	left = leftMotor;
	right = rightMotor;
	
	Scale();
	SetMotors();
	
}

void LNDrive::StopOverride()
{
	overridden = false;
}

void LNDrive::StartFollowLine()
{
	
}

bool LNDrive::StatusFollowLine()
{
	return false;
}

void LNDrive::StopFollowLine()
{
	
}
