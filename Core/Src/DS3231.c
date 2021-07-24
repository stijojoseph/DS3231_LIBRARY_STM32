/*
 * DS3231.c
 *
 *  Created on: 10-Jul-2021
 *      Author: STIJO JOSEPH
 */
#include "main.h"
char *weekday[10]={"","MONDAY","TUESDAY","WEDNESDAY","THURSDAY","FRIDAY","SATURDAY","SUNDAY"};
extern uint16_t Dev;
extern uint8_t pData;
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;
/*
 * @brief time updating definition
 * @param hr
 * The hour of the time
 * @param min
 * The minute of the time
 * @param sec
 * The seconds of the time
 * @param format
 * HR_FORMAT_24  -for 24 hour format time input
 *HR_FORMAT_12_AM  -for 12 hour format time input ,at AM
 *HR_FORMAT_12_PM  --for 12 hour format time input ,at PM
 *
 *@note
 *Bit 6 of the hours register is defined as the 12- or 24-hour mode select bit. When high, the 12-hour mode
 *is selected. In the 12-hour mode, bit 5 is the AM/PM bit with logic-high being PM. In the 24-hour mode, bit 5 is the 20-hour bit (20–23 hours).
 *The century bit (bit 7 of the month register) is toggled when the years register overflows from 99 to 00.The day-of-week register increments at
 *
 */


void time_write(int hr,int min,int sec,int format)
{

	uint8_t MemAddress;
	uint8_t	 pata[3];
	uint16_t Devaddress=(Dev<<1);
	MemAddress=0x00;

	//pata[2]=integer_to_bcd(hr);

	if(format==HR_FORMAT_24)
	pata[2]=integer_to_bcd(hr);
	else
	{
	pata[2]=integer_to_bcd(hr)|(1<<6);
	if(format==HR_FORMAT_12_PM)
		pata[2]=integer_to_bcd(hr)|(1<<6)|(1<<5);
	else if(format==HR_FORMAT_12_AM)
		pata[2]=integer_to_bcd(hr)|(1<<6);
	}

	pata[1]=integer_to_bcd(min);
	pata[0]=integer_to_bcd(sec);



	HAL_I2C_Mem_Write(&hi2c1, Devaddress, MemAddress, 1, &pata,3,1000);


}

/*
 * @brief
 * Function to write the date
 *@param day
 *get the current day of the date
 *@param month
 *get the current month of the date
 *@param year
 *get the current year of the date
 *
 *@note
 *write to the register defined for date
 *date_write(day,month,year)
 *
 */




void date_write(int day,int date,int month,int year)
{

	uint8_t MemAddress;
	uint8_t	 pata[4];
	uint16_t Devaddress=(Dev<<1);
	MemAddress=0x03;
	pata[0]=integer_to_bcd(day);
	pata[1]=integer_to_bcd(date);
	pata[2]=integer_to_bcd(month);
	pata[3]=integer_to_bcd(year);



	HAL_I2C_Mem_Write(&hi2c1, Devaddress, MemAddress, 1, &pata,4,1000);


}

/* Function to read current date or time
 * argument  for reading date
 * read_time(DATE);
 *
 * argument for reading time
 * read_time(TIME);
 *
 *
 */

void read_time()
{
	uint8_t MemAddress=TIME;

	uint16_t Devaddress=(Dev<<1);
	 // HAL_I2C_Master_Transmit(&hi2c1,Devaddress, pData,2,1000);

	  uint8_t data[5];
	  HAL_I2C_Mem_Read(&hi2c1, Devaddress,MemAddress,1,&data,3,1000);
uint8_t second=data[0];
uint8_t minute=data[1];
uint8_t hour=data[2];
char *hour_format="";
int hr1=0;
//if 6th bit is  set which means it follows 12 hour format check 5th bit to know AM /PM
if((hour & (1<<6))!=0)
{
hr1=1;
if((hour & (1<<5))!=0)
{hour_format="PM";
hour &=~(1<<5);
}
else
	hour_format="AM";


}
//else it follows 24 hpour format

hour &=~(1<<6);


hour=bcd_to_integer(hour);
minute=bcd_to_integer(minute);
second=bcd_to_integer(second);
print(int_to_char(hour));
print("-hour");
print(int_to_char(minute));
print("-minute");
print(int_to_char(second));
print("-second");
if(hr1==1)
print(hour_format);


}

void read_date()
{
	uint8_t MemAddress=DATE;

	uint16_t Devaddress=(Dev<<1);
	 // HAL_I2C_Master_Transmit(&hi2c1,Devaddress, pData,2,1000);

	  uint8_t data[5];
	  HAL_I2C_Mem_Read(&hi2c1, Devaddress,MemAddress,1,&data,4,1000);
uint8_t day=data[0];
uint8_t date=data[1];
uint8_t month=data[2];
uint8_t year=data[3];
char *year_format="";

month&=~(1<<7);

year=bcd_to_integer(year);
month=bcd_to_integer(month);
date=bcd_to_integer(date);
print("****************");
print(int_to_char(year));
print("-year");
print(int_to_char(month));
print("-month");
print(int_to_char(date));
print("-date");
print("day-");
print(weekday[day]);
print("****************");


}

/*
 * @brief ALARM SET definition
 * @param hr
 * The hour of the time
 * @param min
 * The minute of the time
 * @param sec
 * The seconds of the time
 * @param format
 * HR_FORMAT_24  -for 24 hour format time input
 *HR_FORMAT_12_AM  -for 12 hour format time input ,at AM
 *HR_FORMAT_12_PM  --for 12 hour format time input ,at PM
 *@param day 1-7 denotes days
 *1-monday
 *2-tuesday...upto 7-sunday
 *@param date
 *date varies from 1-31 denotes date
 *@note

 *
 */


void alarm_write(int hr,int min,int sec,int format,int day,int date,int mode)
{

	uint8_t MemAddress;
	uint8_t	 pata[5];
	uint16_t Devaddress=(Dev<<1);

	MemAddress=CONTROL;
	  uint8_t data;
	  HAL_I2C_Mem_Read(&hi2c1, Devaddress,MemAddress,1,&data,1,1000);
	 data &=0x00;
	//HAL_I2C_Mem_Write(&hi2c1, Devaddress, MemAddress, 1, &data,1,1000);
	 data &=0x05;
	HAL_I2C_Mem_Write(&hi2c1, Devaddress, MemAddress, 1, &data,1,1000);


	MemAddress=ALARM;

	//pata[2]=integer_to_bcd(hr);
	pata[0]=integer_to_bcd(sec);
	pata[1]=integer_to_bcd(min);
	pata[3]=integer_to_bcd(date);

	if(format==HR_FORMAT_24)
	pata[2]=integer_to_bcd(hr);
	else
	{
	pata[2]=integer_to_bcd(hr)|(1<<6);
	if(format==HR_FORMAT_12_PM)
		pata[2]=integer_to_bcd(hr)|(1<<6)|(1<<5);
	else if(format==HR_FORMAT_12_AM)
		pata[2]=integer_to_bcd(hr)|(1<<6);
	}

	switch(mode)
	{
	case ALARM_DY_H_M_S:
	{
		pata[3]|=(1<<6);
	break;
	}
	case ALARM_H_M_S:
	{
		pata[3]|=(1<<7);
		break;
	}
	case ALARM_M_S:
	{
		pata[2]|=(1<<7);
		pata[3]|=(1<<7);
		break;
	}
	case ALARM_S:
	{   pata[1]|=(1<<7);
		pata[2]|=(1<<7);
		pata[3]|=(1<<7);
		break;
	}
	case ALARM_ONCE_PER_SECOND:
	{
		pata[0]|=(1<<7);
		pata[1]|=(1<<7);
		pata[2]|=(1<<7);
		pata[3]|=(1<<7);
		break;
	}

default:
	break;


	}




	HAL_I2C_Mem_Write(&hi2c1, Devaddress, MemAddress, 1, &pata,4,1000);


}


//A10-RX A09-TX
void print(char *data)
{
	HAL_UART_Transmit(&huart1,(char *)data,strlen(data),1000);

}


/*
 * ds3231 rtc timer takes tiemand date input in bcd format
 */


