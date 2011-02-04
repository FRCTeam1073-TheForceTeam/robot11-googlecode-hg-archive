#include "LNDrive.h"

LNDrive::LNDrive(SpeedController *lmj, SpeedController *rmj, Joystick *lj, Joystick *rj, Navigation *n, Encoder *lEnc, Encoder *rEnc)
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
	isTankDrive = true;
}

void LNDrive::PeriodicService()
{
	CheckDriveMode();
	
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
		
	}
	else if (turningToAngle)
	{
		UpdateTurnToAngle();
	}
	else
	{
		if(isTankDrive)
			TankDrive();
		else
			ArcadeDrive();
	}
}

void LNDrive::TankDrive()
{
#if 1
	left = leftJoystick->GetY();
	right = rightJoystick->GetY();
#else
	left = right = leftJoystick->GetZ();
#endif

	if(fabs(left) < .1)
	{
		left = 0;
	}
	
	if(fabs(right) < .1)
	{
		right = 0;
	}
	
	if (leftJoystick->GetRawButton(LeftTurboButton) && rightJoystick->GetRawButton(RightTurboButton))
	{
		if(left != 0)
		{
			left /= fabs(left);
		}
		if (right != 0)
		{
			right /= fabs(right);
		}
	}
	
	Scale();
	SetMotors();
}

void LNDrive::ArcadeDrive()
{
	float x = leftJoystick->GetX();
	float y = leftJoystick->GetY();
	
	left = y + x;
	right = y - x;
	
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
	
	if(currentAngle < 0)
	{
		currentAngle = 360 + currentAngle;
	}
	
	float angleDif = desiredAngle - currentAngle;
	
	if(fabs(angleDif) < 2)
	{
		left = 0;
		right = 0;
	}
	else
	{
		left = angleDif / 360;
		right = -angleDif / 360;
	}
	
	Scale();
	SetMotors();
}

void LNDrive::Override(float leftMotor, float rightMotor)
{
	overridden = true;
	
	left = -leftMotor;
	right = -rightMotor;
	
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
void LNDrive::CheckDriveMode()
{
	bool isButtonTenPressed = leftJoystick->GetRawButton(10);
	static bool wasButtonTenPressed = false;
	
	if(isButtonTenPressed && !wasButtonTenPressed)
	{
		isTankDrive = !isTankDrive;
		printf("isTank = %d\n", isTankDrive);
	}
	wasButtonTenPressed = isButtonTenPressed;
	
}
