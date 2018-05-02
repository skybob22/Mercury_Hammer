#include "VoltMeter.h"
#include <Arduino.h>
#include <SysTimer.h>

voltMeter::voltMeter(const int pin,const int number_of_avg,const double max_volts): input_pin(pin),number_of_average(number_of_avg),current_index(0),max_voltage(max_volts),
last_average(12.5),divider(3){
	voltages = new double[number_of_avg];
	pinMode(input_pin,INPUT);
	update_freq = new sysTimer(250);
}

voltMeter::~voltMeter(){
	delete [] voltages;
}

double voltMeter::map_to_voltage(const int reading){
	double value = ((reading)*max_voltage) / 1023.0;
	return (value);
}

double voltMeter::getVoltage(){
	return (last_average);	
}

bool voltMeter::update(){
	static bool store = false;
	if (update_freq->timerAlarm()){
		if (current_index<number_of_average){
			voltages[current_index] = map_to_voltage(analogRead(input_pin))*divider + 0.20*divider;
			current_index++;
			store = false;
			return (store);
		}
		else{
			current_index = 0;
			last_average = 0;
			for (int i=0;i<number_of_average;i++){
				last_average+=voltages[i];
			}
			last_average = last_average/number_of_average;
			store = true;
			return (store);
		}
	}
	else{
		return (store);
	}
	//Returns true when new average has been taken
}

void voltMeter::setFreq(const long interval){
	update_freq->setTimer(interval);
	update_freq->zero();
}