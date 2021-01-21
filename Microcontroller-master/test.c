#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>

int M[] = {0b10111101,0b10000001,0b11011101,0b11011101,0b11011101,0b10011101,0b10111101,0b11000011} ;


int main(void)
{
    DDRA=0xFF;
    DDRD=0xff;
    int i = 0 ;
    
    int l = 0 ;
    while (1)
    {
        for(l=0;l<100;l++){
            PORTD = 1<<i ;
            PORTA = M[i];
            _delay_ms(2);
            i = (i+1)% 8;
        }
        PORTA = 0xFF;//comment this for not to blink
        _delay_ms(200);//comment this for not to blink


    }
}
