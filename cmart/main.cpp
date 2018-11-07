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
	unsigned long long curprice = 0, totalprice = 0;
	unsigned int flag = 0;
	
    while (1) 
    {
		inputkey = getKey();
		if(mode == NORMAL_MODE)
		{
			displayClock(hou, min, sec);
			if (inputkey == Menu) {mode = MENU_MODE; lcd_clear();}
		}	
		else if (mode == MENU_MODE)
		{
			lcd_putsf(0,0,(unsigned char *)"1: Calculation  ");
			lcd_putsf(0,1,(unsigned char *)"2: Total Sales  ");
			
			if(inputkey == key1) {mode  = CALC_MODE; lcd_clear();}
			else if(inputkey == key2) {mode  = TOTAL_MODE; lcd_clear();}
			inputkey = 0;
			_delay_ms(50);
		}
		else if (mode == CALC_MODE)
		{
			lcd_putsf(0,0,(unsigned char *)"Calculation Mode  ");	
			if(flag ==0)
			{
				if(inputkey == key0) curprice = (curprice * 10) + 0;				
				else if(inputkey == key1) curprice = (curprice * 10) + 1;
				else if(inputkey == key2) curprice = (curprice * 10) + 2;
				else if(inputkey == key3) curprice = (curprice * 10) + 3;
				else if(inputkey == key4) curprice = (curprice * 10) + 4;
				else if(inputkey == key5) curprice = (curprice * 10) + 5;
				else if(inputkey == key6) curprice = (curprice * 10) + 6;
				else if(inputkey == key7) curprice = (curprice * 10) + 7;
				else if(inputkey == key8) curprice = (curprice * 10) + 8;
				else if(inputkey == key9) curprice = (curprice * 10) + 9;
				else if(inputkey == plus)
				{
					 totalprice = totalprice + curprice;
					 curprice = 0;
				}
				flag = 1;
			}
			if (inputkey == 0) flag = 0;
			char str[16];
			sprintf(str, "%ld", curprice);
			lcd_putsf(0, 1, (unsigned char *)str);
		}
		else if (mode == TOTAL_MODE)
		{
			lcd_putsf(0,0,(unsigned char *)"Total Sales Mode  ");
		}
		//언제든 looby 누르면 노말 모드(whenever push lobby, back to normal mode)
		if(inputkey == lobby) mode = NORMAL_MODE;
	}
}

