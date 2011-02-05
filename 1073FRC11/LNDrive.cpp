#include "LNDrive.h"

LNDrive::LNDrive(SpeedController *lmj, SpeedController *rmj, Joystick *lj, Joystick *rj, Navigation *n, Encoders1073 *enc)
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
		//Left blank deliberately, someone else is in control
	}
	else if (turningToAngle)
	{
		UpdateTurnToAngle();
	}
	else
	{
		if(isTankDrive)
		{
			TankDrive();
		}
		else
		{
			ArcadeDrive();
		}
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
	
	float angleDif = desiredAngle - currentAngle;
	
	if(fabs(angleDif) < 5)
	{
		left = 0;
		right = 0;
	}

	else if (angleDif > 0 && angleDif > 180 ||
			 angleDif < 0 && -angleDif < 180)
	{
		left = angleDif / 180;
		right = -left;
	}
	else
	{
		right = angleDif / 180;
		left = -right;
	}
	
	if (fabs(angleDif) < 30 && navigation->GetXVelocity() > .5)
	{
		left *= -1;
		right *= -1;
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

void LNDrive::CheckDriveMode()
{
	bool isButtonTenPressed = leftJoystick->GetRawButton(SwitchDriveModeButton);
	static bool wasButtonTenPressed = false;
	
	if(isButtonTenPressed && !wasButtonTenPressed)
	{
		isTankDrive = !isTankDrive;
		printf("isTank = %d\n", isTankDrive);
	}
	wasButtonTenPressed = isButtonTenPressed;
	
}
