/*kate cherian does not drink toilet water */
/* These comments are not useful */
#include "LNDrive.h"

LNDrive::LNDrive(Jaguar *lmj, Jaguar *rmj, Joystick *lj, Joystick *rj, Navigation *n)
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
	
}

void LNDrive::TankDrive()
{
	left = leftJoystick->GetY();
	right = rightJoystick->GetY();
	
	if(fabs(left) > .1)
	{
		left = 0;
	}
	
	if(fabs(right) > .1)
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
	leftMotorJaguar->Set(left);
	rightMotorJaguar->Set(right);
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
