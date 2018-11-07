#define ENABLE  (PORTC |= 0x04)
#define DISABLE (PORTC &= 0xFB)
#define F_CPU 16000000
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void init_PORTC(void)
{
	DDRC = 0xFF;
	PORTC = 0xFF;
}
unsigned char getkey()
{
	unsigned char key = 0;
	for (int i=0; i<4; i++)
	{
		PORTD = ~(0x00 | (1 << i));
		_delay_ms(5);
		key = (~PIND & 0xf0);
		if (key) return (key | (PORTD & 0x0F));
	}
}
void instrction_out(unsigned char b)
{
	PORTC = b&0xF0;
	ENABLE;
	DISABLE;
	PORTC=((b<<4)&0xF0);
	ENABLE;
	DISABLE;
	_delay_ms(2);
}
void char_out(unsigned char b)
{
	PORTC=(b&0xF0)|0x01;
	ENABLE;
	DISABLE;
	PORTC=((b<<4)&0xF0)|0x01;
	ENABLE;
	DISABLE;
	_delay_ms(2);
}
void lcd_gotoxy(unsigned char x, unsigned char y)
{
	// 16 * 2 Character LCD
	//  Busy();
	switch(y)
	{
		case 0 : instrction_out(0x80+x); break;
		case 1 : instrction_out(0xC0+x); break;
	}
}
void lcd_putsf(unsigned char x, unsigned char y, unsigned char *str)
{
	unsigned int i=0;
	lcd_gotoxy(x,y);
	do
	{
		char_out(str[i]);
	}
	while(str[++i]!='\0');
}
void lcd_init(void)
{
	init_PORTC();
	_delay_ms(200);
	_delay_us(600);
	instrction_out(0x28);
	_delay_ms(200);
	instrction_out(0x28);
	_delay_ms(200);
	instrction_out(0x0C);
	instrction_out(0x06);
	instrction_out(0x02);
	instrction_out(0x01);
	instrction_out(0x01);
}
void lcd_clear(void)
{
	instrction_out(0x01);
	_delay_ms(10);
}

void io_init(void)
{
	MCUCR|=(1<<SRE) | (1<<SRW10);
	XMCRA=(1<<SRL2) | (0<<SRL1) | (0<<SRL0) | (1<<SRW01) | (1<<SRW00) | (1<<SRW11);
	XMCRB |= 0x00;
}
void portInit()
{
	DDRA = 0xff;	//
	DDRB = 0xff;	// 
	DDRD = 0x0f;	// 
	
	TCCR1A = 0x40;
	TCCR1B = 0x09;
}
void powerOn()
{
	lcd_putsf(0, 0,(unsigned char *)"     MARKET");
	lcd_putsf(0, 1,(unsigned char *)"     SYSTEM");
	_delay_ms(500);
	lcd_putsf(0, 0,(unsigned char *)"          ");
	lcd_putsf(0, 1,(unsigned char *)"          ");
	_delay_ms(500);
}
