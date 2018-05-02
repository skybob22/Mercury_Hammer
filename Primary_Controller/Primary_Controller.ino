//------------------------Includes------------------------//
#include <VarSpeedServo.h>
#include <Bounce2.h>

#include "RGB.h"
#include "HammerMode.h"
#include <SysTimer.h>

//-----------------------Definitions (IO Pins)----------------------//
#define servo_pin_1 4 //Arduino
#define servo_pin_2 7 //Ardunio
#define servo_pin_3 8 //Arduino
#define servo_pin_4 9 //Ardunio
#define servo_speed 60


#define LED_red 6 //Arduino
#define LED_green 3 //Arduino
#define LED_blue 5 //Arduino

//Pins A4 and A5 are wired to work with I2C
#define switch_pin A3 //Arduino
#define signal_to_second A4 //Arduino


enum mode_t{
	run_hammer,
	test_code,
};

//-----------------------Setup------------------------//
void setup() {
  pinMode(switch_pin,INPUT_PULLUP);
  pinMode(13,OUTPUT);
  
}

//------------------------Main Program-------------------------//
void loop() {
	static bool first_run = true;
  static HammerMode stance;
  static Bounce toggle_switch;
  static mode_t code_case = run_hammer;
  
  if (first_run){ //Equivilent to setup, but able to access variables from loop
  	first_run = false;
  	stance.attachLights(LED_red,LED_green,LED_blue);
  	stance.attachServos(servo_pin_1,servo_pin_2,servo_pin_3,servo_pin_4);
  	stance.setServoSpeed(servo_speed);
  	toggle_switch.attach(switch_pin);
  	if(digitalRead(switch_pin) == 1){
  		stance.setMode(Hammer);
  	}
  	else{
  		stance.setMode(Cannon);
  	}
  }
  
  toggle_switch.update();
  
  switch(code_case){
  	case run_hammer:
  		if (toggle_switch.rose() || toggle_switch.fell()){
  			stance.toggleMode();
  		}
  		break;
  	
  	case test_code:
			
			break;
  	default:
  		//Something went wrong
  		break;
  }
}
