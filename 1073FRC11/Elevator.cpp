#include <stdio.h>
#include "WPILib.h"
#include "userincludes.h"
#include "Elevator.h"
#include "SmartJoystick.h"
#include "SmartJagMotor.h"
#include "math.h"

//find actual values for brake on, brake off, and maxspeed

static const float leewayfeet = ((1/12)/2.54); //error range for elevator height
static const float Kp = 1.0;
static const float maxSpeed = .5;
static const float servoBrakeOn = -1;
static const float servoBrakeOff = 1.0;
static const float startingPoint = 1; //change later to the height of the base of the robot
static float heights[] = { .5, 1.0, 1.5, 2.0, 2.5, 3.0 };

Elevator::Elevator(SmartJaguarMotorEncoder *ma, SmartJaguarMotorEncoder *mb, Servo *s1, SmartJoystick *e)
{
	motorA = ma;
	motorB = mb;
	servo = s1;
	targetPosition = 0.0;
	joystick = e;
}


void
Elevator::GoToPositionFeet(float ft) // sets the target position
{
	targetPosition = ft;
}
float
Elevator::GetTargetPositionFeet() //modifies and returns target position to account for height - base
{
	return (targetPosition - startingPoint);
}
bool
Elevator::IsAtTargetPosition() // checks to see if the elevator is at the target position, returns true if it is
{
	float current = GetCurrentPositionFeet();
	float dis = (fabs(current - targetPosition));
	
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
		static bool wasButtonElevatorTestPressed = false;	
		static unsigned int testIndex = 0;
		
		bool isButtonElevatorTestPressed = joystick->GetRawButton(ElevatorNextPositionTestButton);
		
		
		if(isButtonElevatorTestPressed && !wasButtonElevatorTestPressed)
		{
			testIndex++;
			if(testIndex > sizeof_array(heights))
				testIndex = 0;
			GoToPositionFeet(heights[testIndex]);	
		}
		wasButtonElevatorTestPressed = isButtonElevatorTestPressed;
}
void
Elevator::PeriodicService()
{
	// For now, add a test for NULL for our motors. Until they are connected to to the bot,
	// we can't do anything
	if ((motorA == NULL) || (motorB == NULL)) return;
	
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
		motorA->ResetEncoder();
		targetPosition = 0;
	}
	
		
	
	float positionNow = GetCurrentPositionFeet();
	
	float err = (targetPosition - positionNow);
	
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
