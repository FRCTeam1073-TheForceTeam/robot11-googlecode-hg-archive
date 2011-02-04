#include "userincludes.h"
#include "LNDrive.h"
#include "Encoders1073.h"

class LineFollower;

class LineFollower
{
	public:
		
		LineFollower(LNDrive *d, Joystick *ljoy, Joystick *rjoy, DigitalInput *llsensor,  DigitalInput *mlsensor, DigitalInput *rlsensor, Encoders1073 *enc);
		void StartInAutonomous();
		void EndInAutonomous();
		void FollowLine();
		void PeriodicService();
		
	private:
		LNDrive *drive; // robot drive system
		Joystick *leftJoystick;
		Joystick *rightJoystick;
		DigitalInput *leftLineSensor;
		DigitalInput *middleLineSensor;
		DigitalInput *rightLineSensor;
		Encoders1073 *encoders;
		bool inAutonomous;
		bool done;
		bool leftIsOn;
		bool rightIsOn;
		bool middleIsOn;
		bool fork;
};
