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
Elevator::GoToPositionFeet(float ft) //sets the position for the elevator to go to
{
	targetposition = ft;
}
float
Elevator::GetTargetPositionFeet() //gets the actual target position, accounting for the robot height - thee elevator
{
	return (targetposition - startingPoint);
}
bool
Elevator::IsAtTargetPosition() //checks if the elevator is at the target position
{
	float current = GetCurrentPositionFeet();
	
	if((fabs(current - targetposition) < leewayfeet))
		return true;
	else
		return false;
}
void
Elevator::SetBrake(bool brake) //brake controls - on & off, self explanitory
{
	if(brake)
		servo->Set(servoBrakeOn);
	else
		servo->Set(servoBrakeOff);
}
float
Elevator::GetCurrentPositionFeet() // gets the current position of the robot
{
	float curposition = motorA->GetPosition();
	
	return curposition;
}
void
Elevator::PeriodicService()
{
	if(isHoming)
	{
		if(motorA->GetReverseLimitOK()) //if the limit switch hasn't been hit
		{
			motorA->Set(-maxSpeed/2); //both move down at half speed, can change to make sure it's not too fast
			motorB->Set(-maxSpeed/2);
			return;
		}
		isHoming = false; //resets all values, stops motors
		motorA->Set(0);
		motorB->Set(0);
		
	}
	
		
	
	float positionNow = GetCurrentPositionFeet();
	
	float err = (targetposition - positionNow);
	
	float output = err*Kp;
	
	if(IsAtTargetPosition()) //sets the brake if at target position
		SetBrake(true);
	else
		SetBrake(false);
	
	if(output > maxSpeed) //makes sure that the elevator does not exceed the max speed
		output = maxSpeed;
	if(output < -maxSpeed)
		output = -maxSpeed;
	
	motorA->Set(output);
	motorB->Set(output);
	
}
