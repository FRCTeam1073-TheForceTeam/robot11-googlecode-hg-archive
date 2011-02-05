//////////////////////////////////////////////////////////
// Filename: Elevator.h
// Author:   
// Date:     January 23, 2011
//
// Description: This file contains the basic camera manager.  It is starting out as a simple stub with a time 
// holdoff to ensure the camera is pwered up and functional prior to program execution.
//
//////////////////////////////////////////////////////////
#ifndef __CameraManager_h__
#define __CameraManager_h__

#include "WPILib.h"
#include "Vision\AxisCamera.h"
#include <stdio.h>


class Elevator
{
	
public:
	Elevator(CANJaguar *ma, CANJaguar *mb, Servo *s1);
	
	void GoToPositionFeet(float ft);
	float GetCurrentPositionFeet();
	bool IsAtTargetPosition();
	float GetTargetPositionFeet();
	void PeriodicService();
	
	
	
private:
	
	void SetBrake(bool brake);
    float targetposition;
    CANJaguar *motorA;
    CANJaguar *motorB;
    Servo *servo;
    bool isHoming;
};

#endif