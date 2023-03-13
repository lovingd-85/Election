#include <REGX52.H>
#include "picture.h"
sbit SCL = P2^0;
sbit SDA = P2^1;

void Delay1ms(unsigned int count)		//@11.0592MHz
{
	unsigned char i, j;
	while(count--){
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}


void II2C_Start(){
    SCL = 1;
    SDA = 1;
    SDA = 0;
    SCL = 0;
}
void II2C_Stop(){
    SCL = 0;
    SDA = 0;
	SCL = 1;
    SDA = 1;
    

}

void II2C_SendByte(unsigned char Byte){
    unsigned i;
    for(i = 0; i < 8; i++){
        SCL = 0;
        SDA = (Byte&(0x80>>i));
        SCL = 1;  
    }
    SCL = 0;

    SDA = 1;
    SCL = 1;//准备接受应答
    SCL = 0;
}

void SSD1306_Command(unsigned char Byte){
/*If D/C# pin is HIGH, D[7:0] is interpreted as 
display data written to Graphic Display Data RAM (GDDRAM). 
If it is LOW, the input at D[7:0] is interpreted as a command. */
    II2C_Start();
    II2C_SendByte(0x78);
    II2C_SendByte(0x00);
    II2C_SendByte(Byte);
    II2C_Stop;
}

void SSD1306_WriteData(unsigned char Data){
    II2C_Start();
    II2C_SendByte(0x78);
    II2C_SendByte(0x40);
    II2C_SendByte(Data);
    II2C_Stop();
}

void Picture(unsigned int num){
    unsigned char x,y;
    unsigned int i=0;
	switch(num){
		case 1:
			for(y=0;y<8;y++){
			  SSD1306_Command(0xb0+y);
			  SSD1306_Command(0x0);
			  SSD1306_Command(0x10);
		
			  for(x=0;x<128;x++)
			  {
				SSD1306_WriteData(page1[i++]);
			  }
			}
			break;
		case 2: break;
	}
}

void HorizontalSroll(){
	unsigned char x,y;
	unsigned int i=0;
	
	while(1){
		SSD1306_Command(0x2E);
		SSD1306_Command(0x26);//水平滚动
		SSD1306_Command(0x00);//虚拟字节
		SSD1306_Command(0x05);//开始页
		SSD1306_Command(0x05);//帧率	
		SSD1306_Command(0x07);//结束页
		SSD1306_Command(0xcd);//开始列
		SSD1306_Command(0xff);//结束列（列的起始在开发文档中没有写到，不加我的会有一点问题，加上就好了。）
		SSD1306_Command(0x2f);//开始滚动
		Delay1ms(820);
		SSD1306_Command(0x2E);
		SSD1306_Command(0x27);//水平滚动
		SSD1306_Command(0x00);//虚拟字节
		SSD1306_Command(0x05);//开始页
		SSD1306_Command(0x05);//帧率	
		SSD1306_Command(0x07);//结束页
		SSD1306_Command(0xcd);//开始列
		SSD1306_Command(0xff);//结束列（列的起始在开发文档中没有写到，不加我的会有一点问题，加上就好了。）
		SSD1306_Command(0x2f);//开始滚动
		Delay1ms(820);
	}
}

void SSD1306_ShowStr(unsigned int x, unsigned int y, unsigned char* words){ 
	unsigned int i = 0,c = 0, j = 0;
	while (words[i] != '\0')
	{
		c = words[i] - 32;
		if(x > 120){  //最后一行写不下
			y+=2;
			x = 0;
		}

		SSD1306_Command(0xb0 + y);
		SSD1306_Command(0x00 + (x%16));
		SSD1306_Command(0x10 + (x/16));
		for(j = 0; j < 8; j++)
		{
			SSD1306_WriteData(F8X16[c][j]);
		}
		SSD1306_Command(0xb1 + y);
		SSD1306_Command(0x00 + (x%16));
		SSD1306_Command(0x10 + (x/16));
		for(j = 8; j < 16; j++)
		{
			SSD1306_WriteData(F8X16[c][j]);
		}
		x+=8;

		i++;
	}
}


void SSD1306_Inital(){
    SSD1306_Command(0xAE);   //display off
	SSD1306_Command(0x20);	//Set Memory Addressing Mode	
	SSD1306_Command(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	SSD1306_Command(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	SSD1306_Command(0xc8);	//Set COM Output Scan Direction
	SSD1306_Command(0x00);//---set low column address
	SSD1306_Command(0x10);//---set high column address
	SSD1306_Command(0x40);//--set start line address
	SSD1306_Command(0x81);//--set contrast control register
	SSD1306_Command(0xdf);
	SSD1306_Command(0xa1);//--set segment re-map 0 to 127
	SSD1306_Command(0xa6);//--set normal display
	SSD1306_Command(0xa8);//--set multiplex ratio(1 to 64)
	SSD1306_Command(0x3F);//
	SSD1306_Command(0xa4);//0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	SSD1306_Command(0xd3);//-set display offset
	SSD1306_Command(0x00);//-not offset
	SSD1306_Command(0xd5);//--set display clock divide ratio/oscillator frequency
	SSD1306_Command(0xf0);//--set divide ratio
	SSD1306_Command(0xd9);//--set pre-charge period
	SSD1306_Command(0x22); //
	SSD1306_Command(0xda);//--set com pins hardware configuration
	SSD1306_Command(0x12);
	SSD1306_Command(0xdb);//--set vcomh
	SSD1306_Command(0x20);//0x20,0.77xVcc
	SSD1306_Command(0x8d);//--set DC-DC enable
	SSD1306_Command(0x14);//
	SSD1306_Command(0xaf);//--turn on oled panel 
}

