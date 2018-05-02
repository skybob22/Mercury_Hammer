#ifndef HAMMERMODE_H
#define HAMMERMODE_H

#include "RGB.h"
#include <VarSpeedServo.h>

enum Mode{
	Hammer,
	Cannon,
};

class HammerMode{
	public:
		HammerMode();
		~HammerMode();
		
		void attachServos(int servo_1,int servo_2,int servo_3,int servo_4);		//Tells the object what pins are used for servo PWM
		void attachLights(int rPin,int gPin,int bPin);												//Sets which pins are to be used for the RGB lighting
		void setServoSpeed(int speed);																				//Controls how fast the servos move
		
		void setMode(Mode stance);																						//Used to set the hammer to either hammer mode or cannon mode
		void toggleMode();																										//Toggles between modes, switches to whichever mode is not active
		Mode getMode();																												//Returns which mode is active
		
	private:
		RGB* RGBptr;
		VarSpeedServo* servo_list[4];
		Mode current_stance;
		int servo_speed;
		int servo_pins[4];
		static const int hammerRGB[3] = {255,55,0}; //Yellow color for hammer
		static const int cannonRGB[3] = {0,160,130}; //Blue/Cyan color for cannon
		static const long hammerServoPos[4] = {1400,1225,1700,700}; //1500,1225,1700,700 in order = old values for hammer
		static const long cannonServoPos[4] = {1050,1600,1300,1100}; //1150,1600,1300,1100 in order = old values for cannon
};

#endif