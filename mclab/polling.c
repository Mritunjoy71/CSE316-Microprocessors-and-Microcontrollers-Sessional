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
            _delay_ms(1000);
        }
        if(in & 0x02)
        {
            if(c<0)c=15;
			else c--;
				PORTA=c;
            _delay_ms(1000);
        }
    }
}

