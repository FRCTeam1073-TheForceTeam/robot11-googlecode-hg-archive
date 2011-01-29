/*kate cherian does not drink toilet water */
/* These comments are not useful */
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
}

void LNDrive::PeriodicService()
{
	TankDrive();
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
