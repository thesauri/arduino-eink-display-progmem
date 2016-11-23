/* Arduino Smart_Eink Library (modified)
 * Copyright (C) 2016 by NOA Labs
 * Author  Bruce Guo (NOA Labs)
 * Modified to use less RAM by Walter Berggren
 *
 * This file is work for Eink.
 *
 * This Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this Library. If not, see
 * <http://www.gnu.org/licenses/>.
 */


#include "SmartEink.h"
#include <SPI.h>
#include <Arduino.h>
#include <avr/pgmspace.h>

const unsigned char F8X16[] PROGMEM =
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,// 0
	0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x33,0x30,0x00,0x00,0x00,//!1
	0x00,0x10,0x0C,0x06,0x10,0x0C,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//"2
	0x40,0xC0,0x78,0x40,0xC0,0x78,0x40,0x00,0x04,0x3F,0x04,0x04,0x3F,0x04,0x04,0x00,//#3
	0x00,0x70,0x88,0xFC,0x08,0x30,0x00,0x00,0x00,0x18,0x20,0xFF,0x21,0x1E,0x00,0x00,//$4
	0xF0,0x08,0xF0,0x00,0xE0,0x18,0x00,0x00,0x00,0x21,0x1C,0x03,0x1E,0x21,0x1E,0x00,//%5
	0x00,0xF0,0x08,0x88,0x70,0x00,0x00,0x00,0x1E,0x21,0x23,0x24,0x19,0x27,0x21,0x10,//&6
	0x10,0x16,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//'7
	0x00,0x00,0x00,0xE0,0x18,0x04,0x02,0x00,0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00,//(8
	0x00,0x02,0x04,0x18,0xE0,0x00,0x00,0x00,0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00,//)9
	0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00,0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00,//*10
	0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x1F,0x01,0x01,0x01,0x00,//+11
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xB0,0x70,0x00,0x00,0x00,0x00,0x00,//,12
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,//-13
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,//.14
	0x00,0x00,0x00,0x00,0x80,0x60,0x18,0x04,0x00,0x60,0x18,0x06,0x01,0x00,0x00,0x00,///15
	0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,//016
	0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//117
	0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,//218
	0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00,//319
	0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00,//420
	0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00,//521
	0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00,//622
	0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,//723
	0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,//824
	0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00,//925
	0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,//:26
	0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x00,0x00,0x00,0x00,//;27
	0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00,//<28
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,//=29
	0x00,0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x20,0x10,0x08,0x04,0x02,0x01,0x00,//>30
	0x00,0x70,0x48,0x08,0x08,0x08,0xF0,0x00,0x00,0x00,0x00,0x30,0x36,0x01,0x00,0x00,//?31
	0xC0,0x30,0xC8,0x28,0xE8,0x10,0xE0,0x00,0x07,0x18,0x27,0x24,0x23,0x14,0x0B,0x00,//@32
	0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20,//A33
	0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00,//B34
	0xC0,0x30,0x08,0x08,0x08,0x08,0x38,0x00,0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00,//C35
	0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00,//D36
	0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x20,0x23,0x20,0x18,0x00,//E37
	0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x00,0x03,0x00,0x00,0x00,//F38
	0xC0,0x30,0x08,0x08,0x08,0x38,0x00,0x00,0x07,0x18,0x20,0x20,0x22,0x1E,0x02,0x00,//G39
	0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x20,0x3F,0x21,0x01,0x01,0x21,0x3F,0x20,//H40
	0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//I41
	0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,0x00,//J42
	0x08,0xF8,0x88,0xC0,0x28,0x18,0x08,0x00,0x20,0x3F,0x20,0x01,0x26,0x38,0x20,0x00,//K43
	0x08,0xF8,0x08,0x00,0x00,0x00,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x20,0x30,0x00,//L44
	0x08,0xF8,0xF8,0x00,0xF8,0xF8,0x08,0x00,0x20,0x3F,0x00,0x3F,0x00,0x3F,0x20,0x00,//M45
	0x08,0xF8,0x30,0xC0,0x00,0x08,0xF8,0x08,0x20,0x3F,0x20,0x00,0x07,0x18,0x3F,0x00,//N46
	0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x10,0x20,0x20,0x20,0x10,0x0F,0x00,//O47
	0x08,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,0x20,0x3F,0x21,0x01,0x01,0x01,0x00,0x00,//P48
	0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x18,0x24,0x24,0x38,0x50,0x4F,0x00,//Q49
	0x08,0xF8,0x88,0x88,0x88,0x88,0x70,0x00,0x20,0x3F,0x20,0x00,0x03,0x0C,0x30,0x20,//R50
	0x00,0x70,0x88,0x08,0x08,0x08,0x38,0x00,0x00,0x38,0x20,0x21,0x21,0x22,0x1C,0x00,//S51
	0x18,0x08,0x08,0xF8,0x08,0x08,0x18,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,//T52
	0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,//U53
	0x08,0x78,0x88,0x00,0x00,0xC8,0x38,0x08,0x00,0x00,0x07,0x38,0x0E,0x01,0x00,0x00,//V54
	0xF8,0x08,0x00,0xF8,0x00,0x08,0xF8,0x00,0x03,0x3C,0x07,0x00,0x07,0x3C,0x03,0x00,//W55
	0x08,0x18,0x68,0x80,0x80,0x68,0x18,0x08,0x20,0x30,0x2C,0x03,0x03,0x2C,0x30,0x20,//X56
	0x08,0x38,0xC8,0x00,0xC8,0x38,0x08,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,//Y57
	0x10,0x08,0x08,0x08,0xC8,0x38,0x08,0x00,0x20,0x38,0x26,0x21,0x20,0x20,0x18,0x00,//Z58
	0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00,//[59
	0x00,0x0C,0x30,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x06,0x38,0xC0,0x00,//\60
	0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,//]61
	0x00,0x00,0x04,0x02,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//^62
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,//_63
	0x00,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//`64
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x19,0x24,0x22,0x22,0x22,0x3F,0x20,//a65
	0x08,0xF8,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x3F,0x11,0x20,0x20,0x11,0x0E,0x00,//b66
	0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x0E,0x11,0x20,0x20,0x20,0x11,0x00,//c67
	0x00,0x00,0x00,0x80,0x80,0x88,0xF8,0x00,0x00,0x0E,0x11,0x20,0x20,0x10,0x3F,0x20,//d68
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x22,0x22,0x22,0x22,0x13,0x00,//e69
	0x00,0x80,0x80,0xF0,0x88,0x88,0x88,0x18,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//f70
	0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x6B,0x94,0x94,0x94,0x93,0x60,0x00,//g71
	0x08,0xF8,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,//h72
	0x00,0x80,0x98,0x98,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//i73
	0x00,0x00,0x00,0x80,0x98,0x98,0x00,0x00,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,//j74
	0x08,0xF8,0x00,0x00,0x80,0x80,0x80,0x00,0x20,0x3F,0x24,0x02,0x2D,0x30,0x20,0x00,//k75
	0x00,0x08,0x08,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//l76
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F,//m77
	0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,//n78
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,//o79
	0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00,0x80,0xFF,0xA1,0x20,0x20,0x11,0x0E,0x00,//p80
	0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x0E,0x11,0x20,0x20,0xA0,0xFF,0x80,//q81
	0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x20,0x20,0x3F,0x21,0x20,0x00,0x01,0x00,//r82
	0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x33,0x24,0x24,0x24,0x24,0x19,0x00,//s83
	0x00,0x80,0x80,0xE0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x1F,0x20,0x20,0x00,0x00,//t84
	0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20,//unsigned char5
	0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x00,0x01,0x0E,0x30,0x08,0x06,0x01,0x00,//v86
	0x80,0x80,0x00,0x80,0x00,0x80,0x80,0x80,0x0F,0x30,0x0C,0x03,0x0C,0x30,0x0F,0x00,//w87
	0x00,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x31,0x2E,0x0E,0x31,0x20,0x00,//x88
	0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x80,0x81,0x8E,0x70,0x18,0x06,0x01,0x00,//y89
	0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x21,0x30,0x2C,0x22,0x21,0x30,0x00,//z90
	0x00,0x00,0x00,0x00,0x80,0x7C,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x3F,0x40,0x40,//{91
	0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,//|92
	0x00,0x02,0x02,0x7C,0x80,0x00,0x00,0x00,0x00,0x40,0x40,0x3F,0x00,0x00,0x00,0x00,//}93
	0x00,0x06,0x01,0x01,0x02,0x02,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//~94
};


/* -------------------------------------------------------------
 private class function, called by public fuction: clearScreen(), to init the screen;
 --------------------------------------------------------------*/
void E_ink::InitEink(void) //initial code
{
	
	SPI.begin();
	
	WriteComm(0x10);//exit deep sleep mode
	WriteData(0x00);
	WriteComm(0x11);//data enter mode
	WriteData(0x03);
	WriteComm(0x44);//set RAM x address start/end, in page 36
	WriteData(0x00);//RAM x address start at 00h;
	WriteData(0x11);//RAM x address end at 11h(17)->72: [because 1F(31)->128 and 12(18)->76]
	WriteComm(0x45);//set RAM y address start/end, in page 37
	WriteData(0x00);//RAM y address start at 00h;
	WriteData(0xAB);//RAM y address start at ABh(171)->172: [because B3(179)->180]
	WriteComm(0x4E);//set RAM x address count to 0;
	WriteData(0x00);
	WriteComm(0x4F);//set RAM y address count to 0;
	WriteData(0x00);
	WriteComm(0xF0);//booster feedback used, in page 37
	WriteData(0x1F);
	WriteComm(0x22);//display updata sequence option ,in page 33
	WriteData(0xC0);//enable sequence: clk -> CP
	
	ConfigureLUTRegister();
	
	WriteComm(0x2C);//vcom
	WriteData(0xA0);
	WriteComm(0x3C);//board
	WriteData(0x63);
	WriteComm(0x22);//display updata sequence option ,in page 33
	WriteData(0xC4);//enable sequence: clk -> CP -> LUT -> initial display -> pattern display
}

/*-------------
 refresh the screen, need to be called by application every time  the screen changed
 --------------*/
void E_ink::RefreshScreen(void)
{
	
	WriteComm(0x20);
	CloseBump();
	delay(5000);
	
}
/*--------------
 Show a full picture in 3096 bytes(2 bits)
 ----------------*/
void E_ink::EinkShowLogo(INT8U *image)
{
	int i;
	WriteComm(0x24);
	for(i=0;i<3096;i++)//3096,1548
	{
		WriteData(image[i]);
	}
}
/*--------------------
 To make a 1548bytes(2 bits) picture become a 3096bytes(1 bits) picture
 ----------------------*/
INT8U E_ink::GetTwoByte(INT8U image)
{
	INT8U i0=0x01,i1=0x02,i2=0x04,i3=0x08;
	
	if((image&0x01)==0x00) i0=0x00;
	if((image&0x02)==0x00) i1=0x00;
	if((image&0x04)==0x00) i2=0x00;
	if((image&0x08)==0x00) i3=0x00;
	
	return ((i3<<4)|(i3<<3)|(i2<<3)|(i2<<2)|(i1<<2)|(i1<<1)|(i0<<1)|i0);
}
/*--------------------
 Show a 1548(2 bits) picture
 -----------------------*/
void E_ink::ShowBitMap(INT8U *image)
{
	int i;
	WriteComm(0x24);
	for(i=0;i<1548;i++)//3096,1548
	{
		WriteData(GetTwoByte(image[i]>>4));
		WriteData(GetTwoByte(image[i]));
	}
}

/*-------------
 clear the original screen, need to be called before writing any data or command to screen ;
 ------------*/
void E_ink::ClearScreen(void)
{
	INT16U i;
	//InitEink();
	WriteComm(0x24);
	for(i=0;i<3096;i++)
	{
		WriteData(0xff);
	}
	delay(1000);
}

/*
 display character in the Eink screen:
 x:the X start address,X value can be 0 to 14;
 y:the Y start  address, Y vlue can  be 171 to 7;
 the charater diplay erea is from x to x+3 in X position and from y to y-7 in Y position
 unicode_char:the character machine code
 */
void E_ink::DisplayChar(INT8U x,INT8U y,INT16U unicodeChar)
{
	INT16U i;
	GetCharMatrixData(unicodeChar);
	ConverCharMatrixData();
	SetPositionXY(x,x+3,y,y-7);
	WriteComm(0x11);     /*data enter mode command */
	WriteData(0x05);     /*set Y-mode:X address is increment and y address decrement */
	WriteComm(0x24);
	for(i=16;i<32;i++)
	{
		WriteData(matrixDataConver[i]);
	}
	for(i=0;i<16;i++)
	{
		WriteData(matrixDataConver[i]);
	}
}

void E_ink::EinkP8x16Str(INT8U y,INT8U x,char ch[])
{
	unsigned char c=0,j=0;
	while (ch[j]!='\0')
	{
		c=ch[j];
		if(x>172)
		{
			x=0;
			y-=2;
		}
		DisplayChar(y,x,c);
		x+=8;
		j++;
	}
	
}

void E_ink::GetCharMatrixData(INT16U unicodeChar)
{
	INT8U c=0,i=0;
	c=unicodeChar-32;
	for(i=0;i<8;i++)
	{
		matrixData[i+8]=~pgm_read_byte_near(F8X16 + (c<<4)+15-i); //~F8X16[(c<<4)+15-i];
	}
	for(i=0;i<8;i++)
	{
		matrixData[i]=~pgm_read_byte_near(F8X16 + (c<<4)+7-i); //~F8X16[(c<<4)+7-i];
	}
}

/*
 setPositionXY:
 Xs --> X start  address   0~17
 Xe --> X end    address   0~17
 Ys --> Y start  address   0~171
 Ye --> Y end    address   0~171
 */
void E_ink::SetPositionXY(INT8U Xs, INT8U Xe,INT8U Ys,INT8U Ye)
{
	WriteComm(0x44);//set RAM x address start/end  command
	WriteData(Xs);
	WriteData(Xe);
	WriteComm(0x45);//set RAM y address start/end  command
	WriteData(Ys);
	WriteData(Ye);
	WriteComm(0x4E);//set RAM x address count to Xs;
	WriteData(Xs);
	WriteComm(0x4F);//set RAM y address count to Ys;
	WriteData(Ys);
}


void E_ink::CloseBump(void)
{
	WriteComm(0x22);
	WriteData(0x03);
	WriteComm(0x20);
}


void E_ink::WriteComm(INT8U command)
{
	Eink_CS1_HIGH;
	Eink_DC_LOW;
	Eink_CS1_LOW;
	SPI.transfer(command);
	Eink_CS1_HIGH;
}

void E_ink::WriteData(INT8U data)
{
	Eink_CS1_HIGH;
	Eink_DC_HIGH;
	Eink_CS1_LOW;
	SPI.transfer(data);
	Eink_CS1_HIGH;
}



void E_ink::ConfigureLUTRegister(void)
{
	INT8U i;
	const static INT8U initData[] PROGMEM = {
  0x00,0x00,0x00,0x55,0x00,0x00,0x55,0x55,0x00,0x55,0x55,0x55,0xAA,0xAA,0xAA,0xAA,
  0x15,0x15,0x15,0x15,0x05,0x05,0x05,0x05,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x22,0xFB,0x22,0x1B,0x00,0x00,0x00,0x00,0x00,0x00,};
	WriteComm(0x32);  //write data to LUT register
	for(i=0;i<90;i++)
		WriteData(pgm_read_word_near(initData + i));
}

/*convert the matrix data:
 origital_data:it is a 8 bit data
 return value:16 bit data
 for example:origital_data is 10100010,and the return data will be 11001100 00001100*/
INT16U E_ink::ConvertData(INT8U OriginalData)
{
	INT8U i,j;
	INT8U data_L,data_H;
	INT8U temp;
	INT16U final_data;
	temp=OriginalData;
	data_L=0;          /* save low  4 bit convert  result */
	data_H=0;          /* save high 4 bit convert  result */
	
	/*--------- convert low 4 bit--------*/
	for(i=0;i<4;i++)
	{
		if(temp&(0x01<<i))           /* judge the i bit if it is 1*/
			data_L |= 0x03<<(2*i);      /* convert the 2*i bit and the (2*i+1??to 1 */
		else
			data_L  &= ~(0x03<<(2*i));  /* convert the 2*i bit and the (2*i+1??to 0 */
	}
	/*------ convert high 4 bit----------*/
	for(i=4;i< 8;i++)
	{
		j=i-4;
		if(temp &(0x01<<i))
			data_H |= 0x03<<(2*j);
		else
			data_H  &= ~(0x03<<(2*j));
	}
	final_data =(data_H<<8)+data_L;
	return final_data;
}

/*
 conver the character matrix data:
 convert the array  matrixdata[] data,and save convert result in array matrixdata_conver[];
 */
void E_ink::ConverCharMatrixData (void)
{
	INT16U tempData;
	INT8U i,j,m;
	INT8U temp;
	for(i=0;i<8;i++)    //convert the first 8 byte data
	{
		tempData=ConvertData(matrixData[i]);
		matrixDataConver[i]=tempData>>8;          //save data at matrixdata_conver[0]~matrixdata_conver[7]
		matrixDataConver[i+8]=tempData;           //save data at matrixdata_conver[8]~matrixdata_conver[15]
	}
	for(i=8;i<16;i++)  //convert the last 8 byte data
	{
		tempData=ConvertData(matrixData[i]);
		matrixDataConver[i+8]=tempData>>8;       //save data at matrixdata_conver[16]~matrixdata[23]
		matrixDataConver[i+16]=tempData;         //save data at matrixdata_conver[24]~matrixdata_conver[31]
	}
	
}
