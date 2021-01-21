#include<avr/io.h> 
#define F_CPU 1000000
#include<util/delay.h>

int main(void)
{
    unsigned char c = 0, in = 0;
    DDRA = 0xFF;
    DDRB = 0b10011111;
    PORTA = c;
    while (1)
    {
        in = PINB;
        if (in & 0b00100000)
        {
            c++;
            PORTA = c;
            _delay_ms(500);
        }
         if (in & 0b01000000)
        {
            c--;
            PORTA = c;
            _delay_ms(500);
        }
    }
}