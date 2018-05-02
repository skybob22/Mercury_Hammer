#include "HammerMode.h"
#include "RGB.h"
#include <Arduino.h>
#include <VarSpeedServo.h>

HammerMode::HammerMode(){
}

HammerMode::~HammerMode(){
	delete [] servo_list;
	delete RGBptr;
}

void HammerMode::attachServos(int servo_1,int servo_2,int servo_3,int servo_4){
	for (int i=0;i<4;i++){
		this->servo_list[i] = new VarSpeedServo;
	}
	this->servo_pins[0]=servo_1;
	this->servo_pins[1]=servo_2;
	this->servo_pins[2]=servo_3;
	this->servo_pins[3]=servo_4;
	for (int i=0;i<4;i++){
		pinMode(servo_pins[i],OUTPUT);
		servo_list[i]->attach(servo_pins[i]);
	}
}

void HammerMode::attachLights(int rPin,int gPin,int bPin){
	this->RGBptr = new RGB(rPin,gPin,bPin);
}

void HammerMode::setServoSpeed(int speed){
	this->servo_speed = speed;
}

void HammerMode::setMode(Mode stance){
	if (stance == Hammer){
		RGBptr->setRGB(hammerRGB[0],hammerRGB[1],hammerRGB[2]);		
		servo_list[0]->slowmove(hammerServoPos[0],servo_speed);
		servo_list[1]->slowmove(hammerServoPos[1],servo_speed);
		servo_list[2]->slowmove(hammerServoPos[2],servo_speed);
		servo_list[3]->slowmove(hammerServoPos[3],servo_speed);
		
		this->current_stance = Hammer;
	}
	else if (stance == Cannon){
		this->RGBptr->setRGB(cannonRGB[0],cannonRGB[1],cannonRGB[2]);
		servo_list[0]->slowmove(cannonServoPos[0],servo_speed);
		servo_list[1]->slowmove(cannonServoPos[1],servo_speed);
		servo_list[2]->slowmove(cannonServoPos[2],servo_speed);
		servo_list[3]->slowmove(cannonServoPos[3],servo_speed);
		this->current_stance = Cannon;
	}
	else{
		//Something went wrong
	}
}

void HammerMode::toggleMode(){
	if (this->current_stance == Hammer){
		this->setMode(Cannon);
	}
	else if (this->current_stance == Cannon){
		this->setMode(Hammer);
	}
	else{
		//Something went wrong
	}
}

Mode HammerMode::getMode(){
	return(this->current_stance);
}