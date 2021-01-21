
#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif


#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.h"


volatile unsigned char result[10];

void func()
{
	int res=ADCW;
	float t=res*5.0/1023;
	result[0]='0' + (unsigned int) (t);
	result[1] = '.';
	t = t - (unsigned int) (t);
	t = t * 10.0;
	result[2] = '0' + (unsigned int) (t);
    t = t - (unsigned int) (t);
	t = t * 10.0;
	result[3] = '0' + (unsigned int) (t);
    t = t - (unsigned int) (t);
	t = t * 10.0;
	result[4] = '0' + (unsigned int) (t);

	result[5] = '\0';
}

int main(void)
{
	DDRD = 0xFF;
	DDRC = 0xFF;
	DDRB = 0xff;

	int i;
	Lcd4_Init();
	Lcd4_Clear();


	ADMUX |= (1<<REFS0);
	ADCSRA|= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);

	while(1)
	{
		
		Lcd4_Set_Cursor(1,1);
		
		Lcd4_Write_String("Voltage in v:");

		ADCSRA|=(1<<ADSC);
		while(!(ADCSRA & (1<<ADIF)));
		ADCSRA|=(1<<ADIF);
		func();
		//Lcd4_Clear();
		Lcd4_Set_Cursor(2,2);
		Lcd4_Write_String(result);
		//portb=buffer;
		
	}
}