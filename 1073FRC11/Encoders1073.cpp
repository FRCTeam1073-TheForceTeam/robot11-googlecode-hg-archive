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

void diff_timespec( timespec &now, timespec &then, timespec &delta)
{
	// Subtract the two 'timespec' structs
	time_t delta_sec = now.tv_sec - then.tv_sec;
	long delta_nano = now.tv_nsec - then.tv_nsec;
	// If we need to borrow, add 1,000,000,000 ns to nano and substract 1 second.
	// There are one billion nanoseconds in a second
	// Assuming a 'long' is at least 32-bits long and has a range of +/- 2 billion 
	if (delta_nano < 0)
	{
		delta_nano += 1000000000l;
		delta_sec -= 1;
	}
	
	// return the result
	delta.tv_sec = delta_sec;
	delta.tv_nsec = delta_nano;
}

Encoders1073::Encoders1073(SmartGyro *g, SmartJaguarMotorEncoder *left, SmartJaguarMotorEncoder *right)
{
	printf("Encoders1073 ctor scale %d\n", left->GetPulsePerFt());	
	
	gyro = g;
	leftJag = left;
	rightJag = right;

	// Initialize all the accumulators to 0
	net_forward = net_lateral = total_forward = total_lateral = 0;
	
	last_time.tv_sec = last_time.tv_nsec = 0;
	
}

void Encoders1073::ResetEncoders()
{		
	leftJag->ResetEncoder();
	rightJag->ResetEncoder();
}

double Encoders1073::DeltaSeconds()
{
	struct timespec current;
	struct timespec delta;
	if (clock_gettime( CLOCK_REALTIME, &current) != 0)
	{
		perror("clock_gettime failed in Encoders1073  ");
		return 0.0;
	}
	
	// Substract the old time from the current time
	// This function will get called on our periodic thread, so 
	// should normally have 0 for seconds
	diff_timespec( current, last_time, delta);
	
	// Save the current time for the next call
	last_time = current;
	
	// 1,000,000,000 (one billion) nanoseconds per second
	// Compute the time in fractions of seconds
	double delta_seconds = delta.tv_sec + (delta.tv_nsec / 1000000000.0);
	return delta_seconds;
}

void Encoders1073::PeriodicService()
{
	// Get the elapsed time since the last call to this service
	double delta_seconds = DeltaSeconds();
	
	// Compute the distance each wheel rotated
	double left_travelled = leftJag->GetNetPosition();	
	double right_travelled = rightJag->GetNetPosition();
	
	// Compute the direction robot moved, relative to the initial orientation
	// if the robot moves in a straight line, angle will be 0
	double angle_radians = gyro->GetAngleRadians();

	double left_forward = left_travelled * cos(angle_radians);
	double left_lateral = left_travelled * sin(angle_radians);
	
	double right_forward = right_travelled * cos(angle_radians);
	double right_lateral = right_travelled * sin(angle_radians);
	
	double avg_forward = (left_forward + right_forward) / 2;
	double avg_lateral = (left_lateral + right_lateral) / 2;
	
	net_forward += avg_forward;
	total_forward += avg_forward;
	
	// The Y velocity is our forward motion (in feet) divided by the seconds (or part thereof)
	last_XYvelocity.second = avg_forward / delta_seconds;
	
	net_lateral += avg_lateral;
	total_lateral += avg_lateral;
	
	// The X velocity is our lateral motion (in feet) divided by the seconds (or part thereof)
	last_XYvelocity.first = avg_lateral / delta_seconds;
		
}


