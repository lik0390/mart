#include "myfunc.h"


unsigned int tcount = 0, hou = 0, min = 0, sec = 0;
int mode = NORMAL_MODE;
ISR(TIMER0_OVF_vect)
{
	tcount++;
	if(tcount >= 61)
	{
		//1second
		sec++;
		if(sec > 59){min ++; sec = 0;}
		if(min > 59){hou ++; min = 0;}
		if(hou > 59){hou = min = sec = 0;}	
		tcount = 0;
	}
}

int main(void)
{
	initsystem();
	unsigned char inputkey = 0;
    while (1) 
    {
		inputkey = getKey();
		if(mode == NORMAL_MODE)
		{
			displayClock(hou, min, sec);
			if (inputkey == Menu) mode = MENU_MODE;
		}	
		else if (mode == MENU_MODE)
		{
			lcd_putsf(0,0,(unsigned char *)"1: Calculation  ");
			lcd_putsf(0,1,(unsigned char *)"2: Total Sales  ");
			if(inputkey == key1) mode  = CALC_MODE;
			else if(inputkey == key2) mode  = TOTAL_MODE;
			inputkey = 0;
			_delay_ms(50);
		}
		else if (mode == CALC_MODE)
		{
			lcd_putsf(0,0,(unsigned char *)"Calculation Mode  ");	
		}
		else if (mode == TOTAL_MODE)
		{
			lcd_putsf(0,0,(unsigned char *)"Total Sales Mode  ");
		}
		if(inputkey == lobby) mode = NORMAL_MODE;
	}
}

