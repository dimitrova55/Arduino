#include <SoftwareSerial.h>

//UART Serial connection
//temp. sensor connected to A0
//Master should send a temp. value to Slave every second

SoftwareSerial mySerial(4,5);
int temp_pin = 54;  //A0
unsigned long time_previous, time_current;

void setup() {
  // put your setup code here, to run once:
  mySerial.begin(9600);
  Serial.begin(9600);
  time_previous = millis();
}

void readTemperature() {
  // Read the value of temp sensor
  int reading = analogRead(temp_pin); 
  // Calculate voltage from ADC value
  float voltage = reading * 5.0 / 1024.0;
  Serial.print (voltage);
  Serial.print (" V : ");
  // Calculate Celsius degree as multiply voltage value by 100
  float temp_C = voltage * 100;
  Serial.print (temp_C);
  Serial.println (" C");
  //String temp = String(temp_C);
  mySerial.print(temp_C);
}

void loop() {
  // put your main code here, to run repeatedly:6
  time_current = millis();
  if(time_current - time_previous >= 1000){
    time_previous = time_current;
    readTemperature();
  }
}
