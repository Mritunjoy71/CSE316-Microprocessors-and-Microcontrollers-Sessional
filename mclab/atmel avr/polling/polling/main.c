/*
 * polling.c
 *
 * Created: 5/20/2018 3:59:39 PM
 * Author : mritunjoy
 */ 

#include<avr/io.h>
#define F_CPU 1000000
#include<util/delay.h>

int main(void)
{
	unsigned char c=0,in=0;
	DDRB = 0b11111100;
	DDRA= 0xFF;

	PORTA = c;
	while(1)
	{
		in = PINB;
		if(in & 0x01)
		{
			c++;
			PORTA = c;
			_delay_ms(200);
		}
		if(in & 0x02)
		{
			c--;
			PORTA = c;
			_delay_ms(200);
		}
	}
}

