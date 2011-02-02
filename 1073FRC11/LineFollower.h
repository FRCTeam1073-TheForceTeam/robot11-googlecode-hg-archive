#include "userincludes.h"
#include "LNDrive.h"

class LineFollower;

class LineFollower
{
	public:
		
		LineFollower(LNDrive *d, Joystick *ljoy, Joystick *rjoy, DigitalInput *llsensor,  DigitalInput *mlsensor, DigitalInput *rlsensor, Encoder *lEnc, Encoder *rEnc);
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
		Encoder *leftEncoder;
		Encoder *rightEncoder;
		bool inAutonomous;
		bool done;
		bool leftIsOn;
		bool rightIsOn;
		bool middleIsOn;
		bool fork;
};
