#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>

#include <avr/interrupt.h> //STEP1
unsigned char c=0;

ISR(INT1_vect) //STEP2
{
    c++;
        
        PORTA=c;
         //_delay_ms(500);
         _delay_ms(1500);
         GIFR=0xFF;
}

ISR(INT2_vect) //STEP2
{
    if(c<0)c=15;
    else c--;
        PORTA=c;
         //_delay_ms(500);
                 _delay_ms(1500);

         GIFR=0xFF;
}


int main(void)
{
     DDRD=0x00;

     DDRB = 0x00;
     DDRA = 0xFF;
     PORTA=c;

    //MCUCR = MCUCR & 0b00001100; //STEP3
    
    MCUCR = 0x0C;
    MCUCSR = 0b01000000;
    GICR = (1 << INT1)|(1<<INT2); //STEP4
    //GIFR=0b10100000;

    sei(); //STEP5

    while (1)
    {
        

    }
}
