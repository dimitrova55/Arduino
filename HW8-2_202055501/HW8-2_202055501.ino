#include <LiquidCrystal.h>

LiquidCrystal lcd(44, 45, 46, 47, 48, 49);
int temp_pin = 55;   //A1
int photo_pin = 56;  //A2
//unsigned long time_current, time_previous;
int temp_value, photo_value;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(temp_pin, INPUT);
  pinMode(photo_pin,INPUT);
  //time_previous = millis();
}

void readTemperature(){
  temp_value = analogRead(temp_pin);
  //calculate voltage from ADC value
  float voltage = temp_value * 5.0/1024.0;
  Serial.print(voltage);
  Serial.print(" V ; ");
  //Calculate Celsius degree as multiply voltage value by 100
  float temp_C = voltage*100;
  Serial.print(temp_C);
  Serial.print(" C, ");
  lcd.setCursor(0,0);
  lcd.print("temp:" + String(temp_C)); 
}

void readIlluminance(){
  photo_value=analogRead(photo_pin);
  Serial.print("ADC : ");
  Serial.print(photo_value);
  //calculate voltage from ADC value
  float voltage = photo_value * 5.0/1024.0;
  Serial.print(", Voltage : ");
  Serial.println(voltage);
  lcd.setCursor(0,1);
  lcd.print("photoVolt:");
  lcd.print(voltage);
}

void loop() {
  // put your main code here, to run repeatedly:
  readTemperature();  
  delay(1000);
  readIlluminance();
  delay(1000);
}
