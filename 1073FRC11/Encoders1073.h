//////////////////////////////////////////////////////////
// Filename: Encoders1073.h
// Author:   Ken Cowan / Greg Cowan
// Date:     January 30, 2011
//
// Description: This file contains class defintion for the Encoders1073 class,
// responible for treating the encoders as a pair, and computing 
// distance travelled
//
//////////////////////////////////////////////////////////
#ifndef ENCODERS1073_H_
#define ENCODERS1073_H_

#include "userincludes.h"
#include "wpilib.h"

class Encoders1073
{
protected:
	CANJaguar *leftJag;
	CANJaguar *rightJag;
	Gyro *gyro;
	
	double initial_left, last_left;
	double initial_right, last_right;
	float initial_rotation, last_rotation;

	double net_forward, net_lateral;

	double total_forward, total_lateral;
	
public:
	Encoders1073(Gyro *g, CANJaguar *leftJag, CANJaguar *rightJag);
	void ResetEncoders();
	void InitEncoders();
	void PeriodicService();
	std::pair<double, double> GetDistance() { return pair<double, double>( leftJag->GetPosition(), rightJag->GetPosition() );}
	
	// The "net" functions work like a trip odometer and will indicate how far the robot has travelled since the last Reset
	double GetNetForwardDistance() { return net_forward; }
	double GetNetLateralDistance() { return net_lateral; }
	void ResetNetDistance() { net_forward = 0; net_lateral = 0; }
	
	// The "total" functions work like a car odometer
	double GetTotalForwardDistance() { return total_forward; }
	double GetTotalLateralDistance() { return total_lateral; }
			
};

#endif