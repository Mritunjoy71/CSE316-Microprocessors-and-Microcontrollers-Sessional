
#ifndef F_CPU
#define F_CPU 1000000
#endif
#define D0 eS_PORTD0
#define D1 eS_PORTD1
#define D2 eS_PORTD2
#define D3 eS_PORTD3
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7
#define Device_Write_address	0xD0			/* Define RTC DS1307 slave address for write operation */
#define Device_Read_address		0xD1			/* Make LSB bit high of slave address for read operation */
#define hour_12_AM				0x40
#define hour_12_PM				0x60
#define hour_24					0x00
//#define ampmi					0x20
#include <avr/io.h>
//#include <stdio.h>
#include "I2C_Master_H_file.h"
//#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
//#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
//#include "I2C_Master_H_file.h"
#//include "LCD16x2_4Bit.h"

#define Device_Write_address	0xD0				/* Define RTC DS1307 slave address for write operation */
#define Device_Read_address 0xD1				/* Make LSB bit high of slave address for read operation */
#define TimeFormat12 0x40				/* Define 12 hour format */

int EEPROM_global_address_write=0;
int EEPROM_global_address_read=0;
int left_log_current_flag=0;
int right_log_current_flag=0;
int left_log_prev_flag=0;
int right_log_prev_flag=0;

int second,minute,hour,day,date,month,year;

bool IsItPM(char hour_)
{
	if(hour_ & (0x20))
	return 1;
	else
	return 0;
}
/*void EEPROM_write(unsigned int EEPROM_address,char data){
	while(EECR & 0x02){}
	EEAR=EEPROM_address;
	EEDR=data;
	EECR=0x04;
	EECR|=0x02;
}
char EEPROM_read(unsigned int EEPROM_address)
{
	while(EECR & 0x02){}
	EEAR=EEPROM_address;
	//EEDR=data;
	//EECR=0x04;
	EECR=0x01;
	return EEDR;

}*/
void RTC_Read_Clock(char read_clock_address)
{
	I2C_Start(Device_Write_address);				/* Start I2C communication with RTC */
	I2C_Write(read_clock_address);					/* Write address to read */
	I2C_Repeated_Start(Device_Read_address);		/* Repeated start with device read address */

	second = I2C_Read_Ack();						/* Read second */
	minute = I2C_Read_Ack();						/* Read minute */
	hour = I2C_Read_Nack();							/* Read hour with Nack */
	I2C_Stop();										/* Stop i2C communication */
}

void RTC_Read_Calendar(char read_calendar_address)
{
	I2C_Start(Device_Write_address);
	I2C_Write(read_calendar_address);
	I2C_Repeated_Start(Device_Read_address);

	day = I2C_Read_Ack();							/* Read day */ 
	date = I2C_Read_Ack();							/* Read date */
	month = I2C_Read_Ack();							/* Read month */
	year = I2C_Read_Nack();							/* Read the year with Nack */
	I2C_Stop();										/* Stop i2C communication */
}

void RTC_Clock_Write(char _hour, char _minute, char _second, char ampm)
{
	_hour |= ampm;
	I2C_Start(Device_Write_address);			/* Start I2C communication with RTC */
	I2C_Write(0);								/* Write on 0 location for second value */
	I2C_Write(_second);							/* Write second value on 00 location */
	I2C_Write(_minute);							/* Write minute value on 01 location */
	I2C_Write(_hour);							/* Write hour value on 02 location */
	I2C_Stop();									/* Stop I2C communication */
}

void RTC_Calendar_Write(char _day, char _date, char _month, char _year)	/* function for calendar */
{
	I2C_Start(Device_Write_address);			/* Start I2C communication with RTC */
	I2C_Write(3);								/* Write on 3 location for day value */
	I2C_Write(_day);							/* Write day value on 03 location */
	I2C_Write(_date);							/* Write date value on 04 location */
	I2C_Write(_month);							/* Write month value on 05 location */
	I2C_Write(_year);							/* Write year value on 06 location */
	I2C_Stop();									/* Stop I2C communication */
}
int main(void)
{
	//I2C_Init();
	//RTC_Clock_Write(0x03, 0x07, 0x00, hour_12_PM);/* Write Hour Minute Second Format */
	//RTC_Calendar_Write(0x02, 0x29, 0x07, 0x18);	/* Write day date month and year */
	char buffer[20];
	char log[20];
	char* days[7]= {"Sat","Sun","Mon","Tue","Wed","Thu","Fri"};
	//I2C_Init();										/* Initialize I2C*/
	DDRD = 0xFF;
	DDRC = 0xFF;
	DDRB = 0x9F;
	
	ADCSRA =0b10000001;
	int i;
	Lcd8_Init();
	Lcd8_Set_Cursor(1,1);
	/*char duffer[20];
	int ii=0;
	for(ii=0;ii<5;ii++)
	duffer[ii]=EEPROM_read(ii);
	Lcd8_Write_String(duffer);*/
	while(1)
	{	//RTC
		Lcd8_Set_Cursor(1,1);
		RTC_Read_Clock(0);							/* Read the clock with second address i.e location is 0 */
		if (hour & TimeFormat12)	
		{
			sprintf(buffer, "%02x:%02x:%02x  ", (hour & 0b00011111), minute, second);
			if(IsItPM(hour))
			strcat(buffer, "PM");
			else
			strcat(buffer, "AM");
			
			Lcd8_Write_String(buffer);
			strcpy(log,buffer);
		}
		
		else
		{
			sprintf(buffer, "%02x:%02x:%02x  ", (hour & 0b00011111), minute, second);
			//Lcd8_Set_Cursor(1,1);
			Lcd8_Write_String(buffer);
		}
		RTC_Read_Calendar(3);						/* Read the calender with day address i.e location is 3 *///
		Lcd8_Set_Cursor(2,1);
	    	sprintf(buffer, "%02x/%02x/%02x %3s ", date, month, year,days[day-1]);
		//sprintf(buffer, "%02x/%2", date);
		Lcd8_Write_String(buffer);
		//PORTB=0x00;



		//light resistor
		ADMUX = 0b11000001;
		ADCSRA |=0b01000000;
		Lcd8_Set_Cursor(1,1);
		//Lcd8_Write_String("electroSome LCD Hello World");
		while(ADCSRA & 0b01000000){}
		float k=ADC*.025;
		int kk=k,flag=0;
		int temp=24;
		char ch[10];
		 itoa (kk,ch,10);
		//Lcd8_Write_String(ch);
		
		//_delay_ms(100);
		if(kk>=temp)
		{	flag=1;
			//PORTB=0x01;
			//_delay_ms(100);
			
		}
		else{
			flag=0;
			//PORTB=0x00;
			//_delay_ms(100);
		}
		//_delay_ms(2000);
		//1st IR sensor
		ADMUX = 0b11000000;
		ADCSRA |=0b01000000;
		Lcd8_Set_Cursor(1,1);
		//Lcd8_Write_String("electroSome LCD Hello World");
		while(ADCSRA & 0b01000000){}
		float k1=ADC*.025;
		int kk1=k1,flag1=0,flag3=1;
		int temp1=25;
		char ch1[10];
		 itoa (kk1,ch1,10);
		if(k1>temp1)
		{
			flag1=0;
			//PORTB=0x00;
			//_delay_ms(100);
		}
		else{
			flag1=1;
			//PORTB=0x01;
			//_delay_ms(100);
		}

		//2nd IR sensor
		ADMUX = 0b11000010;
		ADCSRA |=0b01000000;
		Lcd8_Set_Cursor(1,1);
		//Lcd8_Write_String("electroSome LCD Hello World");
		while(ADCSRA & 0b01000000){}
		float k2=ADC*.025;
		int kk2=k2,flag2=0,flag4=1;
		int temp2=25;
		char ch2[10];
		 itoa (kk2,ch2,10);
		//Lcd8_Write_String(ch1);
		if(k2>temp2)
		{
			flag2=0;
			//PORTB=0x00;
			//_delay_ms(100);
		}
		else{
			flag2=1;
			//PORTB=0x01;
			//_delay_ms(100);
		}
		//_delay_ms(100);
		//3rd sensor IR
		ADMUX = 0b11000011;
		ADCSRA |=0b01000000;
		Lcd8_Set_Cursor(1,1);
		//Lcd8_Write_String("electroSome LCD Hello World");
		while(ADCSRA & 0b01000000){}
		float k3=ADC*.025;
		int kk3=k3,flag5=0,flag6=1;
		int temp3=25;
		char ch3[10];
		 itoa (kk3,ch3,10);
		//Lcd8_Write_String(ch1);
		if(k3>temp3)
		{
			flag5=0;
			//PORTB=0x00;
			//_delay_ms(100);
		}
		else{
			flag5=1;
			//PORTB=0x01;
			//_delay_ms(100);
		}
		//which lights to select
		if(flag)
		{

			if(flag1 && flag5 && flag2)
			{
				PORTB=0x1F;
				/*int length_Of_buffer=strlen(buffer),i;
				char R_array[15];
				memset(R_array,0,15);
				//sprintf(R_array, "%s", buffer);
				eeprom_write_block(buffer,EEPROM_global_address,strlen(buffer));
				
				EEPROM_global_address+=length_Of_buffer;*/
				_delay_ms(100);
			}
			else if(flag1 && flag2)
			{
				PORTB=0x0F;
				/*int length_Of_buffer=strlen(buffer),i;
				for( i=0;i<length_Of_buffer;i++)
				{
					EEPROM_write(EEPROM_global_address+i,buffer[i]);
				}
				EEPROM_global_address+=length_Of_buffer;*/
				_delay_ms(100);
			}
			else if(flag2 && flag5)
			{
				PORTB=0x1E;
				/*int length_Of_buffer=strlen(buffer),i;
				for( i=0;i<length_Of_buffer;i++)
				{
					EEPROM_write(EEPROM_global_address+i,buffer[i]);
				}
				EEPROM_global_address+=length_Of_buffer;*/
				_delay_ms(100);
			}
			else if(flag1 && flag5)
			{
				PORTB=0x1F;
				/*int length_Of_buffer=strlen(buffer),i;
				for( i=0;i<length_Of_buffer;i++)
				{
					EEPROM_write(EEPROM_global_address+i,buffer[i]);
				}
				EEPROM_global_address+=length_Of_buffer;*/
				_delay_ms(100);
			}
			else if(flag2){
				//flag1=0;
				PORTB=0x07<<1;
				/*int length_Of_buffer=strlen(buffer),i;
				for( i=0;i<length_Of_buffer;i++)
				{
					EEPROM_write(EEPROM_global_address+i,buffer[i]);
				}
				EEPROM_global_address+=length_Of_buffer;*/
				_delay_ms(100);
				
			}
			else if(flag5){
				PORTB=0x07<<2;
				/*int length_Of_buffer=strlen(buffer),i;
				for( i=0;i<length_Of_buffer;i++)
				{
					EEPROM_write(EEPROM_global_address+i,buffer[i]);
				}
				EEPROM_global_address+=length_Of_buffer;*/
				_delay_ms(100);
			}
			else if(flag1)
			{
				//flag1=1;
				PORTB=0x07;
				/*int length_Of_buffer=strlen(buffer),i;
				for(i=0;i<length_Of_buffer;i++)
				{
					EEPROM_write(EEPROM_global_address+i,buffer[i]);
				}
				EEPROM_global_address+=length_Of_buffer;*/
				_delay_ms(100);
			}
			else
			{
				PORTB=0x00;
				_delay_ms(100);
			}
		}
		else
		{
			PORTB=0x00;
			_delay_ms(100);
		}
		//log
		
		if(flag1)
		{
				//PORTB=0x1F;
			int length_Of_buffer=strlen(log),i;
			//char R_array[15];
			//memset(R_array,0,15);
			//sprintf(R_array, "%s", buffer);
			strcat(log,"1");
			eeprom_write_block(log,EEPROM_global_address_write,strlen(log));
				
			EEPROM_global_address_write+=(length_Of_buffer+1);
			//int length_Of_buffer=strlen(buffer),i;
			char R_array[15];
			memset(R_array,0,15);
				//PORTB |=0x80;
			eeprom_read_block(R_array,EEPROM_global_address_read,strlen(log));
			Lcd8_Write_String(R_array);
			EEPROM_global_address_read+=length_Of_buffer+1;
			_delay_ms(500);
		}
		/*if(flag2)
		{
				//PORTB=0x1F;
			int length_Of_buffer=strlen(log),i;
			//char R_array[15];
			//memset(R_array,0,15);
			//sprintf(R_array, "%s", buffer);
			strcpy(log,"2");
			eeprom_write_block(log,EEPROM_global_address_write,strlen(log));
				
			EEPROM_global_address_write+=(length_Of_buffer+1);
			//int length_Of_buffer=strlen(buffer),i;
			char R_array[15];
			memset(R_array,0,15);
				//PORTB |=0x80;
			eeprom_read_block(R_array,EEPROM_global_address_read,strlen(log));
			Lcd8_Write_String(R_array);
			EEPROM_global_address_read+=length_Of_buffer+1;
			_delay_ms(1000);
		}
		if(flag5)
		{
				//PORTB=0x1F;
			int length_Of_buffer=strlen(log),i;
			//char R_array[15];
			//memset(R_array,0,15);
			//sprintf(R_array, "%s", buffer);
			strcpy(log,"3");
			eeprom_write_block(log,EEPROM_global_address_write,strlen(log));
				
			EEPROM_global_address_write+=(length_Of_buffer+1);
			//int length_Of_buffer=strlen(buffer),i;
			char R_array[15];
			memset(R_array,0,15);
				//PORTB |=0x80;
			eeprom_read_block(R_array,EEPROM_global_address_read,strlen(log));
			Lcd8_Write_String(R_array);
			EEPROM_global_address_read+=length_Of_buffer+1;
			_delay_ms(1000);
		}*/
		//_delay_ms(5000);
		//left_log_prev_flag=flag1;
		/*if(PINB & 0x20)
		{
			
			
			if(left_log_current_flag && !left_log_prev_flag ){
				int length_Of_buffer=strlen(buffer),i;
				char R_array[15];
				memset(R_array,0,15);
				//PORTB |=0x80;
				eeprom_read_block(R_array,EEPROM_global_address_read,strlen(buffer));
				Lcd8_Write_String(R_array);
				EEPROM_global_address_read+=length_Of_buffer;
			}
			//PORTB &=0x7F;
			left_log_prev_flag= left_log_current_flag;
			//left_log_prev_flag=0;
		}
		else if(PINB & 0x00){
			left_log_prev_flag=0;
			left_log_current_flag=1;
			//left_log
			//PORTB &=0x7F;
		}
		/*for(i=0;i<15;i++)
		{
			_delay_ms(500);
			Lcd8_Shift_Left();
		}
		for(i=0;i<15;i++)
		{
			_delay_ms(500);
			Lcd8_Shift_Right();
		}
		
		Lcd8_Write_Char('e');
		Lcd8_Write_Char('S');
		_delay_ms(500);*/
		Lcd8_Clear();
	}
	
}
