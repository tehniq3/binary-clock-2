// based on video from https://youtu.be/25DEicM0rrg
// based on sketch from http://www.multiwingspan.co.uk/arduino.php?page=bclock
// adapted sketch for 24 hour format by niq_ro from http://arduinotehniq.blogspot.com/
// 01.07.2015 - Craiova
// original schematic for Arduino: http://oi62.tinypic.com/53s0f6.jpg

#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 RTC;

byte AN1 = 8;    // tens (2^0=1) 
byte AN2 = 7;    // tens (2^1=2)
byte AN3 = 6;    // tens (2^2=4)
byte AN4 = 5;    // units (2^0=1)
byte AN5 = 4;    // units (2^1=2)
byte AN6 = 3;    // units (2^2=4)
byte AN7 = 2;    // units (2^3=8)

byte CT1 = 11;    // hours control
byte CT2 = 10;    // minutes control
byte CT3 = 9;    // seconds control

boolean LED1, LED2, LED3, LED4, LED5, LED6;              // leds for hours
boolean LED7, LED8, LED9, LED10, LED11, LED12, LED13;    // leds for minutes
boolean LED14, LED15, LED16, LED17, LED18, LED19, LED20; // leds for seconds

int cloci = 500;  // time in us with units on

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    //RTC.adjust(DateTime(__DATE__, __TIME__));
  }

  pinMode(AN1, OUTPUT);
  pinMode(AN2, OUTPUT);
  pinMode(AN3, OUTPUT);
  pinMode(AN4, OUTPUT);
  pinMode(AN5, OUTPUT);
  pinMode(AN6, OUTPUT);
  pinMode(AN7, OUTPUT);
  
  pinMode(CT1, OUTPUT);
  pinMode(CT1, OUTPUT);
  pinMode(CT1, OUTPUT);
  
}

void loop()
{

  DateTime now = RTC.now();
  // All used for checking the time of the clock
  // This section can be removed when everything is working
  Serial.print(now.day(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.year(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  // End of section that can be removed

  int mins = now.minute();
  int secs = now.second();
  int hr = now.hour();

// split values in numbers for tens and units
  int zo = hr / 10;
  int uo = hr - zo * 10;
  int zm = mins /10;
  int um = mins - zm * 10;
  int zs = secs / 10;
  int us = secs - zs * 10;

// for tens of hours
if (bitRead(zo,0)==1) LED1 = HIGH; else LED1 = LOW;
if (bitRead(zo,1)==1) LED2 = HIGH; else LED2 = LOW;
// for units of hours
if (bitRead(uo,0)==1) LED3 = HIGH; else LED3 = LOW; 
if (bitRead(zo,1)==1) LED4 = HIGH; else LED4 = LOW;
if (bitRead(zo,2)==1) LED5 = HIGH; else LED5 = LOW;
if (bitRead(zo,3)==1) LED6 = HIGH; else LED6 = LOW;
// for tens of minutes
if (bitRead(zm,0)==1) LED7 = HIGH; else LED7 = LOW; 
if (bitRead(zm,1)==1) LED8 = HIGH; else LED8 = LOW;
if (bitRead(zm,2)==1) LED9 = HIGH; else LED9 = LOW;
// for units of minutes
if (bitRead(um,0)==1) LED10 = HIGH; else LED10 = LOW; 
if (bitRead(zm,1)==1) LED11 = HIGH; else LED11 = LOW;
if (bitRead(zm,2)==1) LED12 = HIGH; else LED12 = LOW;
if (bitRead(zm,3)==1) LED13 = HIGH; else LED13 = LOW;
// for tens of seconds
if (bitRead(zs,0)==1) LED14 = HIGH; else LED14 = LOW; 
if (bitRead(zs,1)==1) LED15 = HIGH; else LED15 = LOW;
if (bitRead(zs,2)==1) LED16 = HIGH; else LED16 = LOW;
// for units of seconds
if (bitRead(us,0)==1) LED17 = HIGH; else LED17 = LOW; 
if (bitRead(zs,1)==1) LED18 = HIGH; else LED18 = LOW;
if (bitRead(zs,2)==1) LED19 = HIGH; else LED19 = LOW;
if (bitRead(zs,3)==1) LED20 = HIGH; else LED20 = LOW;


for(int bucla = 0 ; bucla < 200 ; bucla++) {

// display hours;
digitalWrite(CT1, HIGH);
digitalWrite(CT2, LOW);
digitalWrite(CT3, LOW);
digitalWrite(AN1, LED1);
digitalWrite(AN2, LED2);
digitalWrite(AN3, LOW);  // is not used in hours
digitalWrite(AN4, LED3);
digitalWrite(AN5, LED4);
digitalWrite(AN6, LED5);
digitalWrite(AN7, LED6);
delayMicroseconds(cloci);

// display minutes;
digitalWrite(CT1, LOW);
digitalWrite(CT2, HIGH);
digitalWrite(CT3, LOW);
digitalWrite(AN1, LED7);
digitalWrite(AN2, LED8);
digitalWrite(AN3, LED9);
digitalWrite(AN4, LED10);
digitalWrite(AN5, LED11);
digitalWrite(AN6, LED12);
digitalWrite(AN7, LED13);
delayMicroseconds(cloci);

// display secundes;
digitalWrite(CT1, LOW);
digitalWrite(CT2, LOW);
digitalWrite(CT3, HIGH);
digitalWrite(AN1, LED14);
digitalWrite(AN2, LED15);
digitalWrite(AN3, LED16);
digitalWrite(AN4, LED17);
digitalWrite(AN5, LED18);
digitalWrite(AN6, LED19);
digitalWrite(AN7, LED20);
delayMicroseconds(cloci);
}

}
