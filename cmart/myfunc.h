#ifndef MYFUNC_H_
#define MYFUNC_H_

#include "lcd.h"

void initsystem()
{
	DDRA = 0xff;	//0, 1 : motor 	 | 5,6,7 : RGY LED	
	DDRD = 0x0f;	//0 ~ 3: Row 0~3 | 4 ~ 7 : Col 4 ~ 7
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
}


#endif /* MYFUNC_H_ */