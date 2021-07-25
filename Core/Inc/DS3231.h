/*
 * DS3231.h
 *
 *  Created on: 10-Jul-2021
 *      Author: STIJO JOSEPH
 */

#ifndef INC_DS3231_H_
#define INC_DS3231_H_

#define DATE 0x03
#define TIME 0x00
#define ALARM 0x07
#define CONTROL 0x0E
#define CONTROL_STATUS 0x0F

#define HR_FORMAT_24 0
#define HR_FORMAT_12_AM 1
#define HR_FORMAT_12_PM 2
#define MONDAY 1
#define TUESDAY 2
#define WEDNESDAY 3
#define THURSDAY 4
#define FRIDAY 5
#define SATURDAY 6
#define SUNDAY 7

#define ALARM_DY_H_M_S 0  //Alarm when day, hours, minutes, and seconds match
#define ALARM_DT_H_M_S 1 //Alarm when date, hours, minutes, and seconds match
#define ALARM_H_M_S 2    //Alarm when hours, minutes, and seconds match
#define ALARM_M_S 3      //Alarm when minutes and seconds match
#define ALARM_S 4         //Alarm when seconds match
#define ALARM_ONCE_PER_SECOND 5  //Alarm once per second

#define ALARM2 0x0B
#define ALARM_ONCE_PER_MIN 0
#define ALARM_M 1
#define ALARM_H_M 2
#define ALARM_DT_H_M 3
#define ALARM_DY_H_M 4


#define ALARM_A2F (1UL<<1)
#define ALARM_A1F (1UL<<0)

#define ALARM_A11E (1UL<<0)
#define ALARM_A21E (1UL<<1)
#define CONTROL_INTCN (1UL<<2)

void time_write(int hr,int min,int sec,int format);

void alarm_write(int hr,int min,int sec,int format,int day,int date,int mode);
void date_write(int day,int date,int month,int year);
void alarm_write2(int hr,int min,int format,int day,int date,int mode);
void read_time();
void read_date();
void print(char *data);




















#endif /* INC_DS3231_H_ */
