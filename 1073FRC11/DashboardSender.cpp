//////////////////////////////////////////////////////////
// Filename: Dashboardender.cpp
// Author:   
// Date:     January 23, 2011
//
// Description: This file contains class defintion for the DashBoardSender responible for sending all data 
// to the custom dashboard.
//
//////////////////////////////////////////////////////////

/* print statements can be commented in/out for debug purposes.
 * not everythhing has a printf... YET.
 */

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
	static unsigned int packetCt = 0;
	float tempFloat;
	DriverStation *ds = DriverStation::GetInstance();
	Dashboard &dash = ds->GetHighPriorityDashboardPacker();
	dash.AddCluster();
	
	dash.AddU32(packetCt++);
	dash.AddU32(0xFFFFFFFF);
	dash.AddU16(5);
	
	
	for (int i = 1; i <= 8; i++) {
		tempFloat = (float) AnalogModule::GetInstance(1)->GetAverageVoltage(i);
		dash.AddFloat(tempFloat); // analogs
		//printf("Float %d = %fV\n", i, tempFloat);
	}
	int module = 4;
	dash.AddU8(DigitalModule::GetInstance(module)->GetRelayForward()); // relays (forward)
	dash.AddU8(DigitalModule::GetInstance(module)->GetRelayReverse()); // relays (reverse)
	
	//printf("Relay Forward = %02X\n", DigitalModule::GetInstance(module)->GetRelayForward());
	//printf("Relay Backward = %02X\n", DigitalModule::GetInstance(module)->GetRelayReverse());
	
	dash.AddU16((short)DigitalModule::GetInstance(module)->GetDIO()); // state
	dash.AddU16(DigitalModule::GetInstance(module)->GetDIODirection());//direction
	//printf("Digital IO = %04X\n", (short)DigitalModule::GetInstance(module)->GetDIO());
	//printf("Digital Direction = %04X\n", (short)DigitalModule::GetInstance(module)->GetDIODirection());
	for (int i = 1; i <= 10; i++) {
			dash.AddU8((unsigned char) DigitalModule::GetInstance(module)->GetPWM(i)); // pwm's
			//printf("PWM %d %02X\n" ,i, DigitalModule::GetInstance(module)->GetPWM(i));
	}
	dash.AddFloat(4.0); //time left ...
	dash.AddFloat(ds->GetBatteryVoltage());
	dash.AddFloat(gyro->GetAngle());
	dash.AddFloat(leftJoystick->GetX());
	dash.AddFloat(rightJoystick->GetX());
	dash.AddFloat(leftJoystick->GetY());
	dash.AddFloat(rightJoystick->GetY());
	dash.AddFloat(leftEncoder->GetDistance());
	dash.AddFloat(rightEncoder->GetDistance());
#if 0
	dash.AddFloat(2); //x accel
	dash.AddFloat(2); //y accel
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
	
	
	dash.FinalizeCluster();
	dash.Finalize();
	
}
void
DashboardSender::SendConstants()
{
//	
}
