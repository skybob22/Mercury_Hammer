//--------------------------------------------Includes----------------------------------------------//
#include <MCP23S17.h>
#include <SPI.h>
#include <SysTimer.h>
#include <Bounce2.h>

#include "MCPDisplay.h"
#include "VoltMeter.h"

//Pins A4 & A5 for input/I2C
//Pins 10,11,12,13 used for SPI
//Pins 7,8 used for transciever

//------------------------------------------Global Variables----------------------------------------//
//Expander pins for seven segment display
#define s_a 1 //Display Expander
#define s_b 2 //Display Expander
#define s_c 7 //Display Expander
#define s_d 6 //Display Expander
#define s_e 5 //Display Expander
#define s_f 3 //Display Expander
#define s_g 4 //Display Expander
#define s_dp 8 //Display Expander

//Voltage Measurements
#define volt_ref_pin A7
#define voltage_loss_pin 2 //Interrupt Pin 2

//Light Controls
#define l_pin1 9 //Switch between bright or dim, or 5v supply for pot depending on mode
#define l_pin2 A6 //Pot value or brightness down depending on mode, Has pulldown resistor
#define l_pin3 A1 //brightness up or toggle between bright and dim depending on mode
#define light_mode_pin 4 //On-board switch to select which light mode to use

#define high_power_pin 3 //In digital Mode, controls whether LEDs are bright or dim

enum light_mode_t{
	digital,
	manual,
};

//----------------------------------------Declare Functions---------------------------------//
int getPercent(double voltage);


//---------------------Setup------------------//
void setup() {
  pinMode(high_power_pin,OUTPUT);
  pinMode(volt_ref_pin,INPUT);
  pinMode(light_mode_pin,INPUT_PULLUP);
}


//-----------------Main Program-----------------/
void loop() {
	static bool first_run = true;
	static MCPDisplay ssd(1,10);
	static voltMeter volt_ref(volt_ref_pin,200);
	
	static Bounce light_mode_switch;
	static light_mode_t light_mode;
	static Bounce brightness_toggle;
	static Bounce* switches[] = {&light_mode_switch,&brightness_toggle};

	if (first_run){ //Equivilent to setup, but able to access variables from loop
		first_run = false;
		ssd.attachPins(s_a,s_b,s_c,s_d,s_e,s_f,s_g,s_dp);
		light_mode_switch.attach(light_mode_pin);
		volt_ref.setFreq(100);
		
		//Configure brightness controller
		/*if (digitalRead(light_mode_pin)==0){ //Digital Control Mode
			digitalWrite(l_pin1,LOW); //In case was high supplying Pot voltage before
			pinMode(l_pin1,INPUT_PULLUP);
			pinMode(l_pin2,INPUT_PULLUP); //Has pulldown resisor
			pinMode(l_pin3,INPUT_PULLUP);
			brightness_toggle.attach(l_pin1);
			light_mode = digital;
			
			brightness_toggle.update();
			digitalWrite(high_power_pin,!brightness_toggle.read());
		}
		else if (digitalRead(light_mode_pin)==1){ //Pot Control Mode
			pinMode(l_pin1,OUTPUT);
			pinMode(l_pin2,INPUT); //Has pulldown resistor
			digitalWrite(l_pin2,LOW); //Disable Pullup
			pinMode(l_pin3,INPUT_PULLUP);
			brightness_toggle.attach(l_pin3);
			light_mode = manual;
			Serial.println("Enabled Manual Mode");
			
			brightness_toggle.update();
			digitalWrite(high_power_pin,!brightness_toggle.read());
			
		}*/
		
		if(digitalRead(light_mode_pin)==1){
			pinMode(l_pin1,OUTPUT);
			pinMode(l_pin2,INPUT);//Has pulldown resistor
			pinMode(l_pin3,INPUT_PULLUP);
			light_mode = manual;
			
			digitalWrite(l_pin1,!digitalRead(l_pin3));
			brightness_toggle.attach(l_pin3);
		}
		
	}
	
	
	//Light Brightness
	for (int i=0;i<2;i++){
		switches[i]->update();
	}
	
	if (light_mode == manual){
		static double control_voltage;
		control_voltage = analogRead(l_pin2)*5.17/1018;
		if(brightness_toggle.fell()){
			digitalWrite(l_pin1,HIGH); //Supply 5V to the pot
		}
		else if(brightness_toggle.rose()){
			digitalWrite(l_pin1,LOW); //Disconnect 5V supply to pot, grounding it
		}
	}
	
	
	//Voltage Display
	ssd.writeSegment('p',volt_ref.update());
	double battery_voltage = volt_ref.getVoltage();
	int battery_percentage = getPercent(battery_voltage);
	ssd.display(static_cast<int>(floor(battery_percentage/10)));

	
	//Acceleration Gate Transmitter
	
}







//-----------------------------------------Function Definitions-----------------------------------------//
int getPercent(double voltage){
	if (voltage > 12.3){
		return (100);
	}
	else if(voltage <= 12.3 && voltage >12){
		return (80);
	}
	else if(voltage <= 12 && voltage > 11.6){
		return (70);
	}
	else if(voltage <= 11.6 && voltage > 11.4){
		return (60);
	}
	else if(voltage <= 11.4 && voltage > 11){
		return (50);
	}
	else if(voltage <= 11 && voltage > 10.85){
		return (40);
	}
	else if(voltage <= 10.85 && voltage > 10.7){
		return (30);
	}
	else if(voltage <= 10.70 && voltage > 10.58){
		return (20);
	}
	else if(voltage <= 10.58 && voltage > 10.53){
		return (10);
	}
	else if(voltage <= 10.53){
		return (0);
	}
	else {
		return (0);
	}
}