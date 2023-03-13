#ifndef __DRIVE_H_
#define __DRIVE_H_
void Delay1ms(unsigned int count);
void SSD1306_Command(unsigned char Byte);
void SSD1306_WriteData(unsigned char Data);
void SSD1306_Inital();
void Picture(unsigned int num);
void HorizontalSroll();
void SSD1306_ShowStr(unsigned int x, unsigned int y, unsigned char* words);

#endif