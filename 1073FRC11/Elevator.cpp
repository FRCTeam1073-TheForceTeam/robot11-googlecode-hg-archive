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
const float startingPoint = 1; //change later to the height of the base of the robot
float heights[] = { .5, 1.0, 1.5, 2.0, 2.5, 3.0 };

Elevator::Elevator(CANJaguar *ma, CANJaguar *mb, Servo *s1, Joystick *e)
{
	motorA = ma;
	motorB = mb;
	servo = s1;
	targetposition = 5.0;
	joystick = e;
}


void
Elevator::GoToPositionFeet(float ft) // sets the target position
{
	targetposition = ft;
}
float
Elevator::GetTargetPositionFeet() //modifies and returns target position to account for height - base
{
	return (targetposition - startingPoint);
}
bool
Elevator::IsAtTargetPosition() // checks to see if the elevator is at the target position, returns true if it is
{
	float current = GetCurrentPositionFeet();
	float dis = (fabs(current - targetposition));
	
	if(dis < leewayfeet)
	{
		//printf("Distance: &f\n",dis); //weird warning, fix later
		return true;
	}
	else
		return false;
}
void
Elevator::SetBrake(bool brake) // sets the brake on if true and off otherwise, self explanitory
{
	if(brake)
		servo->Set(servoBrakeOn);
	else
		servo->Set(servoBrakeOff);
}
float
Elevator::GetCurrentPositionFeet() //returns the current elevator position
{
	float curposition = motorA->GetPosition();
	
	return curposition;
}
void
Elevator::GoToPositionIndex(int index)
{
	GoToPositionFeet(heights[index-1]);
}
void
Elevator::CheckJoystick()
{
		bool isButtonTenPressed = joystick->GetRawButton(12);
		static bool wasButtonTenPressed = false;
		int c = 0;
		
		if(isButtonTenPressed && !wasButtonTenPressed)
		{
			GoToPositionFeet(heights[c]);
			c++;
			if(c >= 5)
				c = 0;
		}
		wasButtonTenPressed = isButtonTenPressed;
}
void
Elevator::PeriodicService()
{
	CheckJoystick();
	
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
	
	if(IsAtTargetPosition()) //brakes if at the target position
		SetBrake(true);
	else
		SetBrake(false);
	
	if(output > maxSpeed) //makes sure the elevator doesn't exceed a set max speed
		output = maxSpeed;
	if(output < -maxSpeed)
		output = -maxSpeed;
	
	motorA->Set(output);
	motorB->Set(output);
	
}
