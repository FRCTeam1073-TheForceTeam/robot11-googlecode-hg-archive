//////////////////////////////////////////////////////////
// Filename: Encoders1073.cpp
// Author:   Ken Cowan / Greg Cowan
// Date:     January 30, 2011
//
// This file contains the implementation for the Encoders1073 class,
// responible for treating the encoders as a pair, and computing 
// distance travelled
//
//////////////////////////////////////////////////////////
#include "Encoders1073.h"

static const double PI = 2*acos(0.0);
// Wheel is .5 foot diameter.  We found by experimenting 962 pulses per rotation of wheel
static int encoderCodes = 600; // found through experimentation

	
float mod360(float lhs) 
{
	if (lhs > 360.0f)
		return lhs - int(lhs/360.0f) * 360.0f;
	else
		return lhs;
}

void ResetOne(CANJaguar *jag)
{
	CANJaguar::ControlMode oldMode = jag->GetControlMode();
	jag->ChangeControlMode(CANJaguar::kPosition);
	jag->DisableControl();
	jag->EnableControl(0.0);
	jag->ChangeControlMode(oldMode);
}

void InitOne(CANJaguar *jag)
{
	jag->SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
	
	jag->ConfigEncoderCodesPerRev(encoderCodes);
	
	ResetOne(jag);
}

Encoders1073::Encoders1073(Gyro *g, CANJaguar *left, CANJaguar *right)
{
	printf("Encoders1073 ctor scale %d\n", encoderCodes);	
	
	gyro = g;
	leftJag = left;
	rightJag = right;
	
	InitEncoders();
	
	initial_rotation = last_rotation = mod360(gyro->GetAngle()); 
	initial_left = last_left = leftJag->GetPosition();
	initial_right = last_right = rightJag->GetPosition();

	// Initialize all the accumulators to 0
	net_forward = net_lateral = total_forward = total_lateral = 0;
	
}


void Encoders1073::ResetEncoders()
{		
		ResetOne(leftJag);
		ResetOne(rightJag);
}
void Encoders1073::InitEncoders()
{
	InitOne(leftJag);
	InitOne(rightJag);
}

void Encoders1073::PeriodicService()
{
	double left = leftJag->GetPosition();
	double right = rightJag->GetPosition();
	float rotation = mod360(gyro->GetAngle());
	
	// Compute the distance each wheel rotated
	double left_travelled = left - last_left;
	last_left = left;
	
	double right_travelled = right - last_right;
	last_right = right;
	
	// Compute the direction robot moved, relative to the initial orientation
	// if the robot moves in a straight line, angle will be 0
	double angle = rotation - initial_rotation;
	double angle_radians = angle * PI / 180;
	
	last_rotation = rotation;

	double left_forward = left_travelled * cos(angle_radians);
	double left_lateral = left_travelled * sin(angle_radians);
	
	double right_forward = right_travelled * cos(angle_radians);
	double right_lateral = right_travelled * sin(angle_radians);
	
	net_forward += (left_forward + right_forward) / 2;
	total_forward += (left_forward + right_forward) / 2;
	
	net_lateral += (left_lateral + right_lateral) / 2;
	total_lateral += (left_lateral + right_lateral) / 2;
	
}



