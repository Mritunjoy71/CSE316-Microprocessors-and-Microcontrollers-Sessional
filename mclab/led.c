#include<avr/io.h> 
#define F_CPU 1000000
#include<util/delay.h>
#include <avr/interrupt.h>

int s[] = {0xFF,0xFF,0x03,0xFF,0xFF,0xC0,0xFF,0xFF} ;
int ss[] = {0xFF,0x3,0xFF,0xFF,0xC0,0xFF,0xFF,0xFF};
int a[] = {0b01111110,0xFF,0b11000011,0b11000011,0xFF,0xFF,0b11000011,0b11000011} ;

int d[9];

void tot(int c){
}

int main(void)
{
    DDRA = 0xFF ; //a coloumn , d row
    DDRD = 0xFF ;
    PORTA = 0xFF ; PORTD = 0x00 ;
    
    
    
    
    
    int i = 0 ;
    while(1){
        i = i%8 ;
        PORTD = ~(1<<i) ;
        //for(int i=0; i<8; i++){
       // PORTA = ss[i] ;
       // }
        _delay_ms(2) ;
         i++ ;
        // if(i==8) PORTD = 0xFF ;
    } 
}