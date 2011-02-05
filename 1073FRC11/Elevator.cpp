#include <stdio.h>
#include "WPILib.h"
#include "Elevator.h"
#include "math.h"

//find actual values for brake on, brake off, and maxspeed

const float leewayfeet = ((1/12)/2.54); //error range for elevator height
const float Kp = 1.0;
const float maxSpeed = .5;
const float servoBrakeOn = -1;
const float servoBrakeOff = 1.0;
const float startingPoint = 1; //change later to height to base of elevator

Elevator::Elevator(CANJaguar *ma, CANJaguar *mb, Servo *s1)
{
	motorA = ma;
	motorB = mb;
	servo = s1;
	targetposition = 5.0;
}


void
Elevator::GoToPositionFeet(float ft)
{
	targetposition = ft;
}
float
Elevator::GetTargetPositionFeet()
{
	return (targetposition - startingPoint);
}
bool
Elevator::IsAtTargetPosition()
{
	float current = GetCurrentPositionFeet();
	float dis = (fabs(current - targetposition));
	if(dis < leewayfeet){
	printf("Distance: &f\n",dis);
		return true;}
	else
		return false;
}
}
void
Elevator::SetBrake(bool brake)
{
	if(brake)
		servo->Set(servoBrakeOn);
	else
		servo->Set(servoBrakeOff);
}
float
Elevator::GetCurrentPositionFeet()
{
	float curposition = motorA->GetPosition();
	
	return curposition;
}
void
Elevator::PeriodicService()
{
	if(isHoming)
	{
		if(motorA->GetReverseLimitOK())
		{
			motorA->Set(-maxSpeed/2); //both move down at half speed, can change to accomodate for others
			motorB->Set(-maxSpeed/2);
			return;
		}
		isHoming = false;
		motorA->Set(0);
		motorB->Set(0);
		
	}
	
		
	
	float positionNow = GetCurrentPositionFeet();
	
	float err = (targetposition - positionNow);
	
	float output = err*Kp;
	
	if(IsAtTargetPosition())
		SetBrake(true);
	else
		SetBrake(false);
	
	if(output > maxSpeed)
		output = maxSpeed;
	if(output < -maxSpeed)
		output = -maxSpeed;
	
	motorA->Set(output);
	motorB->Set(output);
	
}
