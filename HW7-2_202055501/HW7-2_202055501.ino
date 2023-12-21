#include <pitches.h>

//play note using a potentiometer;
//divide voltage of a potentiometer into 9 stages then play:
//Silence, Do, Re, Mi, Fa, Sol, La, Si, Do at each stage

int speakerPin = 57;       //A3
int potentiometer = 56;    //A2
int rest = 0;
int tonetoPlay = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(potentiometer, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int adc = analogRead(potentiometer);
  
  //adc = map(adc, 0,1023, 0, 511);    //ne stava
  //tonetoPlay = (adc>>9) +1;          //ne stava
  
  tonetoPlay = 0;                                        //zero for silence
  if (adc >=1 && adc <=128) tonetoPlay = 264;            //do
  else if (adc >= 129 && adc <= 256) tonetoPlay = 297;   //re
  else if (adc >= 257 && adc <=384) tonetoPlay = 330;    //mi
  else if (adc >= 385 && adc <=512) tonetoPlay = 352;    //fa
  else if (adc >= 513 && adc <=640) tonetoPlay = 396;    //sol
  else if (adc >= 641 && adc <=768) tonetoPlay = 440;    //la
  else if (adc >= 769 && adc <=896) tonetoPlay = 495;    //si
  else if (adc >= 897 && adc <=1023) tonetoPlay = 528;   //do
  tone(speakerPin, tonetoPlay, 5);
}
