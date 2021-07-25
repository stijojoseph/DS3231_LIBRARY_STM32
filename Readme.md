Readme.md
 Created on: Jul 24, 2021
     Author: stijo joseph

### DS3231_LIBRARY_STM32 USING HAL I2C
Complete library for Ds3231 for interacting with Stm32 over I2C(HAL LIBRARY) write time,date,day Read time,date,day set alarm
API Definitions are given in the source file and header files 


Printf function prints it to the uart1
/* Writing time to Ds3231 registers */

uint8_t hr=10;
uint8_t min=15;
uint8_t sec=19;

time_write(hr,min,sec,HR_FORMAT_12_PM);



int day=MONDAY;
int date=18;
int month=7;
int year=21;

/* Writing date to Ds3231 registers */
date_write(day,date,month,year);

/* Reading time */
read_time();

/* reading date */
read_date();




ds3231 library for stm32 Ds3231 library
