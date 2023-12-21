/*****************************************************************************/
//	Function:    Get the accelemeter of X/Y/Z axis and print out on the 
//					serial monitor.
//  Hardware:    3-Axis Digital Accelerometer(��16g)
//	Arduino IDE: Arduino-1.0
//	Author:	 Frankie.Chu		
//	Date: 	 Jan 11,2013
//	Version: v1.0
//	by www.seeedstudio.com
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
/*******************************************************************************/

#include <Wire.h>
#include <ADXL345.h>
#include <math.h>


ADXL345 adxl; //variable adxl is an instance of the ADXL345 library
int led1pin = 2, led2pin = 3;
int led1state = false, led2state = false;
int countTap = 0, countShake = 0;
int cur_x,cur_y,cur_z;
int prev_x, prev_y, prev_z;

void setup(){
  Serial.begin(9600);
  adxl.powerOn();

  //set activity/ inactivity thresholds (0-255)
  adxl.setActivityThreshold(75); //62.5mg per increment
  adxl.setInactivityThreshold(75); //62.5mg per increment
  adxl.setTimeInactivity(10); // how many seconds of no activity is inactive?
 
  //look of activity movement on this axes - 1 == on; 0 == off 
  adxl.setActivityX(1);
  adxl.setActivityY(1);
  adxl.setActivityZ(1);
 
  //look of inactivity movement on this axes - 1 == on; 0 == off
  adxl.setInactivityX(1);
  adxl.setInactivityY(1);
  adxl.setInactivityZ(1);
 
  //look of tap movement on this axes - 1 == on; 0 == off
  adxl.setTapDetectionOnX(0);
  adxl.setTapDetectionOnY(0);
  adxl.setTapDetectionOnZ(1);
 
  //set values for what is a tap, and what is a double tap (0-255)
  adxl.setTapThreshold(50); //62.5mg per increment
  adxl.setTapDuration(15); //625us per increment
  adxl.setDoubleTapLatency(80); //1.25ms per increment
  adxl.setDoubleTapWindow(200); //1.25ms per increment
 
  //set values for what is considered freefall (0-255)
  adxl.setFreeFallThreshold(7); //(5 - 9) recommended - 62.5mg per increment
  adxl.setFreeFallDuration(45); //(20 - 70) recommended - 5ms per increment
 
  //setting all interrupts to take place on int pin 1
  //I had issues with int pin 2, was unable to reset it
  adxl.setInterruptMapping( ADXL345_INT_SINGLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_DOUBLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_FREE_FALL_BIT,    ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_ACTIVITY_BIT,     ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_INACTIVITY_BIT,   ADXL345_INT1_PIN );
 
  //register interrupt actions - 1 == on; 0 == off  
  adxl.setInterrupt( ADXL345_INT_SINGLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_DOUBLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_FREE_FALL_BIT,  1);
  adxl.setInterrupt( ADXL345_INT_ACTIVITY_BIT,   1);
  adxl.setInterrupt( ADXL345_INT_INACTIVITY_BIT, 1);

  pinMode(led1pin, OUTPUT);
  pinMode(led2pin, OUTPUT);
  digitalWrite(led1pin, led1state);
  digitalWrite(led2pin, led2state);
  adxl.readXYZ(&prev_x, &prev_y, &prev_z); //read the accelerometer values and store them in variables  x,y,z
  
}

void loop(){
  
	//read interrupts source and look for triggerd actions
  byte interrupts = adxl.getInterruptSource();
  //tap
  if(adxl.triggered(interrupts, ADXL345_SINGLE_TAP)){
    Serial.println("tap");
    led1state = !led1state;
    digitalWrite(led1pin, led1state);
    countTap++;
    Serial.println("countTap = " + String(countTap));
  }

  adxl.readXYZ(&cur_x, &cur_y, &cur_z); //read the accelerometer values and store them in variables  x,y,z
  int diff_x = cur_x - prev_x;
  int diff_y = cur_y - prev_y;
  int diff_z = cur_z - prev_z;
  
  //if(adxl.triggered(interrupts, ADXL345_FREE_FALL))
  //if(adxl.triggered(interrupts, ADXL345_ACCTIVITY))

  if(abs(diff_x)>=30 && abs(diff_y)>=30 && abs(diff_z)>=30)  
  {
    Serial.print("values of X , Y , Z: ");
    Serial.print(cur_x);
    Serial.print(" , ");
    Serial.print(cur_y);
    Serial.print(" , ");
    Serial.println(cur_z);
    led2state = !led2state;
    digitalWrite(led2pin, led2state);
    countShake++;
    Serial.println("countShake = " + String(countShake));
    prev_x = cur_x; prev_y = cur_y; prev_z = cur_z;
    delay(1000);   
  } 
}
