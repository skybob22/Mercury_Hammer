#include "MCPDisplay.h"
#include <Arduino.h>
#include <MCP23S17.h>
#include <SPI.h>

MCPDisplay::MCPDisplay(int adress,int ss_pin){
	this->driver = new MCP(adress,ss_pin);
	driver->begin();
}

MCPDisplay::~MCPDisplay(){
	delete driver;
}

void MCPDisplay::attachPins(const int s_1,const int s_2,const int s_3,const int s_4,const int s_5,const int s_6,const int s_7,const int s_8){
	segment_pins[0] = s_1;
	segment_pins[1] = s_2;
	segment_pins[2] = s_3;
	segment_pins[3] = s_4;
	segment_pins[4] = s_5;
	segment_pins[5] = s_6;
	segment_pins[6] = s_7;
	segment_pins[7] = s_8;
	for (int i=0;i<8;i++){
		driver->pinMode(segment_pins[i],OUTPUT);
		driver->digitalWrite(segment_pins[i],HIGH);
	}
}

void MCPDisplay::writeSegment(int segment_number,bool state){
	driver->digitalWrite(segment_pins[segment_number-1],!state);
}

void MCPDisplay::writeSegment(const char segment_char,bool state){
	if (segment_char == 'p'){
		writeSegment(8,state);
	}
	else{
		int segment_number = static_cast<int>(segment_char)-'a';
		if (segment_number >= 0 && segment_number <=7){
			writeSegment(segment_number+1,state);
		}
	}
}

void MCPDisplay::writeAll(bool a,bool b,bool c,bool d,bool e,bool f,bool g){
	writeSegment('a',a);
	writeSegment('b',b);
	writeSegment('c',c);
	writeSegment('d',d);
	writeSegment('e',e);
	writeSegment('f',f);
	writeSegment('g',g);
}

void MCPDisplay::display(const int number_to_display){
	switch (number_to_display){
		case 0:
			writeAll(1,1,1,1,1,1,0);
			break;
		case 1:
			writeAll(0,1,1,0,0,0,0);
			break;
		case 2:
			writeAll(1,1,0,1,1,0,1);
			break;
		case 3:
			writeAll(1,1,1,1,0,0,1);
			break;
		case 4:
			writeAll(0,1,1,0,0,1,1);
			break;
		case 5:
			writeAll(1,0,1,1,0,1,1);
			break;
		case 6:
			writeAll(1,0,1,1,1,1,1);
			break;
		case 7:
			writeAll(1,1,1,0,0,0,0);
			break;
		case 8:
			writeAll(1,1,1,1,1,1,1);
			break;
		case 9:
			writeAll(1,1,1,1,0,1,1);
			break;
		case 10:
			this->display('F');
			break;
		default:
			//Invalid Number Entered
			writeAll(0,1,1,0,1,1,0);
			break;
	}
}

void MCPDisplay::display(const char char_to_display){
	switch(char_to_display){
		case 'A':
			writeAll(1,1,1,0,1,1,1);
			break;
		case 'C':
			writeAll(1,0,0,1,1,1,0);
			break;
		case 'E':
			writeAll(1,0,0,1,1,1,1);
			break;
		case 'F':
			writeAll(1,0,0,0,1,1,1);
			break;
		case 'H':
			writeAll(0,1,1,0,1,1,1);
			break;
		case 'L':
			writeAll(0,0,0,1,1,1,0);
			break;
		case 'P':
			writeAll(1,1,0,0,1,1,1);
			break;
		case 'U':
			writeAll(0,1,1,1,1,1,0);
			break;
		default:
			//Invalid Letter
			writeAll(0,1,1,0,1,1,0);
			break;
	}
}