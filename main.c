#include <REGX52.H>
#include "drive.h"
void main(){
	SSD1306_Inital();
	Delay1ms(10);
//	Picture(1);
//	HorizontalSroll();
//	Delay1ms(10);
	SSD1306_ShowStr(0, 0, "Hellow!I need you, please give ma a caffee! thinks.");
	while(1){}
}