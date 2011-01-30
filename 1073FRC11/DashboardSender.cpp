//////////////////////////////////////////////////////////
// Filename: Dashboardender.cpp
// Author:   
// Date:     January 23, 2011
//
// Description: This file contains class defintion for the DashBoardSender responible for sending all data 
// to the custom dashboard.
//
//////////////////////////////////////////////////////////
#include "DashboardSender.h"

DashboardSender::DashboardSender(DriverStation *dash, 
		Encoder *lEncoder, Encoder *rEncoder, 
		Joystick *lJ, Joystick *rJ,
		Gyro *gyr)
: ds(dash), 
leftEncoder(lEncoder), rightEncoder(rEncoder), 
leftJoystick(lJ), rightJoystick(rJ),
gyro(gyr)
{
	
}


void
DashboardSender::SendData()
{
	Dashboard &dash = DriverStation::GetInstance()->GetHighPriorityDashboardPacker();
	dash.AddCluster();
	
dash.AddU32(0xFF0001FF);
dash.AddU32(0x0F0F00FF);
dash.AddU32(109);
dash.AddU32(0xFFFFFFFF);
dash.AddU32(0x00000000);
dash.AddU32(0xFFFFFFFF);
dash.AddU32(0x00000000);
dash.AddU32(0xFFFFFFFF);
dash.AddU32(0x00000000);
dash.AddU32(0xFFFFFFFF);
dash.AddU32(0x00000000);
dash.AddU32(0xFFFFFFFF);
dash.AddU32(0x00000000);
dash.AddU32(0xFFFFFFFF);
dash.AddU32(0x00000000);
dash.AddU32(0xFFFFFFFF);
dash.AddU32(0x00000000);
dash.AddU32(0xFFFFFFFF);
dash.AddU32(0x00000000);
dash.AddU32(0xFFFFFFFF);
dash.AddU32(0x00000000);
dash.AddU32(0xFFFFFFFF);
dash.AddU32(0x00000000);
dash.AddU32(0xFFFFFFFF);
dash.AddU32(0x00000000);
dash.AddU32(0xFFFFFFFF);
dash.AddU32(0x00000000);
dash.AddU32(0xFFFFFFFF);
dash.AddU32(0x00000000);


	dash.AddFloat(gyro->GetAngle());
	
	
#if 0
	dash.AddFloat(2);
	dash.AddFloat(2);
	dash.AddFloat(navigation->GetXVel());
	dash.AddFloat(navigation->GetYVel());
	dash.AddFloat(navigation->GetX());
	dash.AddFloat(navigation->GetY());
	dash.AddFloat(navigation->GetSX());
	dash.AddFloat(navigation->GetSY());
	dash.AddI32(leftEncoder->GetRaw());
	dash.AddI32(rightEncoder->GetRaw());
	dash.AddFloat(leftMotorJaguar->Get());
	dash.AddFloat(rightMotorJaguar->Get());
	dash.AddFloat(0);   // DesiredSpeed
#endif 
	dash.AddFloat(0);   // DesiredAngle
	dash.AddU32(0);     // LastRetroAcquisition
	dash.AddU16(0);     // ushort[6] Columns
	dash.AddFloat(0);   // columnAngle
	dash.AddFloat(0);   // verticalAngle
	dash.AddFloat(0);   // RetroXEst
	dash.AddFloat(0);   // RetroYEst
	dash.AddFloat(0);   // ArmHeight
	dash.AddFloat(0);   // DesiredArmHeight
	dash.AddFloat(0);   // ArmMotor
	dash.AddFloat(0);   // ElevatorHeight
	dash.AddFloat(0);   // DesiredElevatorHeight
	dash.AddFloat(0);   // ElevatorMotor
	
	dash.FinalizeCluster();
	dash.Finalize();
	
}

void
DashboardSender::SendConstants()
{
	
}
