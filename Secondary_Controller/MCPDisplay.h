#ifndef MCPDISPLAY_H
#define MCPDISPLAY_H

#include <MCP23S17.h>

class MCPDisplay{
	public:
		MCPDisplay(int adress,int ss_pin);
		~MCPDisplay();
		
		void attachPins(const int s_1,const int s_2,const int s_3,const int s_4,const int s_5,const int s_6,const int s_7,const int s_8);
		
		void display(const int number_to_display);
		void display(const char char_to_display);
		
		void writeSegment(int segment_number,bool state);
		void writeSegment(const char segment_char,bool state);
		void writeAll(bool a,bool b,bool c,bool d,bool e,bool f,bool g);
		
	private:
		MCP* driver;
		int segment_pins[8];
};

#endif