#ifndef VOLTMETER_H
#define VOLTMETER_H

#include <SysTimer.h>

class voltMeter{
	public:
		voltMeter(const int pin,const int number_of_avg,const double max_volts=5);
		//Contructor for voltmeter object, pin = voltage monitor pin, number_of_avg = how many times it samples the voltage to calculate average
		~voltMeter();
		
		bool update();																//Call this in loop in order to take voltage reading
		void setFreq(const long interval);						//Sets how often the object should sample the voltage
		double getVoltage();													//Gets the current average voltage
		
	private:
		double map_to_voltage(const int reading);			//Maps the 0-1023 reading to a voltage 0-(max_volts)
		
		double divider;
		const int input_pin;
		const int max_voltage;
		int current_index;
		const int number_of_average;
		double* voltages;
		double last_average;
		sysTimer* update_freq;
};

#endif