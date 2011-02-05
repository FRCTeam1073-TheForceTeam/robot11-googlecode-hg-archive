#include "LineFollower.h"

LineFollower::LineFollower(LNDrive *d, Joystick *ljoy, Joystick *rjoy, DigitalInput *llsensor,  DigitalInput *mlsensor, DigitalInput *rlsensor, Encoders1073 *enc)
{
	drive = d;
	leftJoystick = ljoy;
	rightJoystick = rjoy;
	leftLineSensor = llsensor;
	middleLineSensor = mlsensor;
	rightLineSensor = rlsensor;
	encoders = enc;
	done = false; 
}

void LineFollower::PeriodicService()
{
//	if (inAutonomous || rightJoystick->GetRawButton(LineFollowButton))
//	{
		FollowLine();
	//}
	//else
	//{
	//	drive->StopOverride();
	//}
}

void LineFollower::StartInAutonomous()
{
	inAutonomous = true;
}

void LineFollower::EndInAutonomous()
{
	inAutonomous = false;
}

void LineFollower::FollowLine(void)
{	
	const float maxSpeed = 0.4;
	std::pair<float, float> lrDistance = encoders->GetDistance();
	if (!done && lrDistance.first)
	{
		leftIsOn = leftLineSensor->Get();
		middleIsOn = middleLineSensor->Get();
		rightIsOn = rightLineSensor->Get();
		
		if (!done && encoders->GetNetForwardDistance() > 7.5 && encoders->GetNetForwardDistance() < 8.0)
		{
			drive->Override(maxSpeed / 3, maxSpeed);
		}
		if (middleIsOn && !leftIsOn && !rightIsOn)
		{
			drive->Override(maxSpeed, maxSpeed);
		}
		else if (leftIsOn && middleIsOn && !rightIsOn)
		{
			drive->Override(maxSpeed, maxSpeed / 2);
		}
		else if (rightIsOn && middleIsOn && !leftIsOn)
		{
			drive->Override(maxSpeed / 2, maxSpeed);
		}
		else if (leftIsOn && !middleIsOn && !rightIsOn)
		{
			drive->Override(maxSpeed, maxSpeed / 3);
		}
		else if (leftIsOn && rightIsOn && !middleIsOn)
		{
			drive->Override(maxSpeed, maxSpeed / 2);
		}
		else if (rightIsOn && !middleIsOn && !leftIsOn)
		{
			drive->Override(maxSpeed / 3, maxSpeed);
		}
		else if (leftIsOn && middleIsOn && rightIsOn)
		{
			drive->Override(maxSpeed / 2, maxSpeed / 2);
			//drive->Override(0.1, 0.1);
			
			//if (rightIsOn && leftIsOn && !middleIsOn)
			//{
				//fork = true;
				//drive->Override(0.25, 0.1);
				//printf("fork\n");
			//}
			//else if (!rightIsOn && !leftIsOn && !middleIsOn)
			//{
					//drive->Override(0.1, 0.1);
					//printf("none\n");
			//}
				
				// hang ubertube
		} 
		//printf("l:%d m:%d r:%d\n", leftIsOn, middleIsOn, rightIsOn);
	}
	else
	{
		drive->Override(0.0, 0.0);
		//printf("l:%d m:%d r:%d\n", leftIsOn, middleIsOn, rightIsOn);
	}
}

