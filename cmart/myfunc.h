#ifndef MYFUNC_H_
#define MYFUNC_H_

#define NORMAL_MODE 0
#define MENU_MODE 1
#define CALC_MODE 2
#define TOTAL_MODE 3

#define key0 231
#define key1 238
#define key2 222
#define key3 190
#define key4 237
#define key5 221
#define key6 189
#define key7 235
#define key8 219
#define key9 187
#define plus 126
#define Enter 125
#define Menu 123
#define change 183
#define lobby 119

#include "lcd.h"

unsigned char getKey()
{
	unsigned char key = 0;
	for (int i = 0; i < 4; i++)
	{
		PORTD = ~(0x00 | ( 1<< i));
		_delay_ms(5);
		key = (~PIND & 0xf0);
		if (key) return PIND;
	}
	return 0;
}

void initsystem()
{
	DDRA = 0xff;	//0, 1 : motor 	 | 5,6,7 : RGY LED	
	DDRD = 0x0f;	//0 ~ 3: Row 0~3 | 4 ~ 7 : Col 4 ~ 7
	TIMSK = 0x01;
	TCCR0 = 0x07;	//1024분주
	lcd_init();
	lcd_clear();
	for(int i = 0; i < 2; i++)
	{
		lcd_putsf(0, 0, (unsigned char *)"     MARKET     ");
		lcd_putsf(0, 0, (unsigned char *)"     SYSTEM     ");
		PORTA = 0b00000000;
		_delay_ms(100);
		lcd_clear();
		PORTA = 0b11100000;
		_delay_ms(100);
	}
	sei(); //Global Interrupt Enable
}

void displayClock(unsigned int hou, unsigned int min, unsigned int sec)
{
	char str[16];
	sprintf(str, "   %02d:%02d:%02d   ", hou , min, sec);
	lcd_putsf(0, 0, (unsigned char *)"    WELCOME!    ");
	lcd_putsf(0, 1, (unsigned char *)str);
}


#endif /* MYFUNC_H_ */