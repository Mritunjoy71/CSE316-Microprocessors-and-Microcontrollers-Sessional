#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>

int M[] = {0b10111101,0b10000001,0b11011101,0b11011101,0b11011101,0b10011101,0b10111101,0b11000011,0b10111101,0b10000001,0b11011101,0b11011101,0b11011101,0b10011101,0b10111101,0b11000011} ;


int main(void)
{
    DDRA=0xFF;
    DDRD=0xff;
    int k = 0 ;
    
    int l = 0 ;
    while (1)
    {
        int i;
        for(i=0;i<8;i++)
        {
            char B[8]={};
            int j;
            for(j=0;j<8;j++)
            {
                B[j]=M[i+j];
            }
            for(l=0;l<300;l++){
                PORTD = 1<<k ;
                PORTA = B[k];
                _delay_ms(2);
                k = (k+1)% 8;
            }
             //_delay_ms(35);
        }

        


        // PORTA = 0xFF;
        // _delay_ms(200);


    }
}
