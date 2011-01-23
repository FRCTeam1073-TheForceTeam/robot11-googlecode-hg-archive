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
	
	dash.AddU16(0xF37A);
	for (int i = 1; i <= 8; i++)
		dash.AddFloat((float) AnalogModule::GetInstance(1)->GetAverageVoltage(i)); // analogs

	int module = 4;
	dash.AddU8(DigitalModule::GetInstance(module)->GetRelayForward()); // relays (forward)
	dash.AddU8(DigitalModule::GetInstance(module)->GetRelayReverse()); // relays (reverse)
#if 0		
	dash.AddU16((short)DigitalModule::GetInstance(module)->GetDIO()); // state
	dash.AddU16(DigitalModule::GetInstance(module)->GetDIODirection());//direction


	for (int i = 1; i <= 10; i++)
				dash.AddU8((unsigned char) DigitalModule::GetInstance(module)->GetPWM(i)); // pwm's
	
	dash.AddU8((char)0x55);

	unsigned short miscDataByte = 0;
	if(true){ miscDataByte = miscDataByte + 1; } // supposed to be teleoperated
	if(ds->IsAutonomous()){ miscDataByte = miscDataByte + 2; }
	if(ds->IsEnabled()){ miscDataByte = miscDataByte + 4; }
	if(ds->GetAlliance() == 1 /*kBlue*/){ miscDataByte += 8; }
		
	if(leftJoystick->GetButton(Joystick::kTriggerButton)){miscDataByte += 16;} // supposed to be diagnostic buttons
	if(rightJoystick->GetButton(Joystick::kTriggerButton)){miscDataByte += 32;}
	
	dash.AddFloat(ds->GetBatteryVoltage()); // battery voltage
	dash.AddFloat(leftJoystick->GetX()); // leftJoystick x-axis
	dash.AddFloat(leftJoystick->GetY()); // leftJoystick y-axis
	dash.AddFloat(rightJoystick->GetX()); // rightJoystick x-axis
	dash.AddFloat(rightJoystick->GetY()); // rightJoystick y-axis
	dash.AddFloat(gyro->GetAngle()); // gyro yaw
	//printf("heading = %f\n",navigation->GetHeading());
	dash.AddFloat((float)leftEncoder->GetDistance()); // left encoder
	dash.AddFloat((float)rightEncoder->GetDistance()); // right encoder
	
	// port #'s
	dash.AddU8(PWM_LeftMotorPort); // l motor
	dash.AddU8(PWM_RightMotorPort); // r motor
#endif	
	dash.FinalizeCluster();
	dash.Finalize();
	
}
