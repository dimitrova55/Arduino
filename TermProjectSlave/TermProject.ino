#include <LiquidCrystal.h>
#include<SoftwareSerial.h>
#include <Servo.h>
#define Fan 5

//SoftwareSerial mySerail(4,5);

LiquidCrystal lcd(44, 45, 46, 47, 48,49); //lcd 연결
Servo myServo1; 
Servo myServo2; 
Servo myServo3;

int trig = 2; 
int echo = 3;
bool isWinOpen = false;
int humLevel, dustLevel, temperature;
unsigned int time_prev, time_curr;

byte user1[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B11111,
  B11111,
  B01110,
  B00000
};

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  lcd.createChar(0, user1);
  lcd.begin(16,2);  //lcd 초기화

  pinMode(Fan, OUTPUT);
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  myServo1.attach(9);
  myServo2.attach(10);
  myServo3.attach(11) ;
  time_prev = millis();
}

void sanitizer(){
  digitalWrite(trig, LOW);
  digitalWrite(echo, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  unsigned long duration = pulseIn(echo, HIGH);

  float distance = duration / 29.0 / 2.0;
  if(distance<10) 
  {
    lcd.clear();    
    lcd.print("Wear a mask!"); 
    lcd.setCursor(16,0);   
    lcd.write(byte(0));      
    //delay(250);
    myServo1.write(180); //180
    myServo2.write(180);
    delay(1000);
  }
  else
  {    
    myServo1.write(0);
    myServo2.write(0); //180 
    //lcd.clear();
  }  
}

void fanOn(){
  int fanSpeed=255;
  analogWrite(Fan,fanSpeed);
//  for(fanSpeed = 0; fanSpeed <= 255; fanSpeed += 10){
//   analogWrite(Fan, fanSpeed);
//   //Serial.print(String(fanSpeed) + " ");
//   //delay(40); 
//  }
  Serial.println("fan on");
}

void fanOff(){
  digitalWrite(Fan,false);
  Serial.println("fan off");
}

void window(int temp, int humid,int dust){
  time_curr = millis();
  if(temp< 22 || humid>7 || dust>3){
    if(time_curr - time_prev >= 10000){
      time_prev = time_curr;
      myServo3.write(90);
      fanOff();
      isWinOpen = true;
      delay(2000);
      return;
    }
    myServo3.write(0);
    isWinOpen = false;  
    fanOn();
    //delay(1000);
  }
  else{
//    if(time_curr - time_prev >= 10000){
//      time_prev = time_curr;
//      myServo3.write(0);
//      fanOn();
//      isWinOpen = false;
//      delay(1000);
//      return;
//    }
    myServo3.write(90);
    fanOff();
    isWinOpen = true;
    //delay(2000);     
  }
}

void loop() {
  sanitizer();
      
  if(Serial1.available()){
    char dust = Serial1.read();
    dustLevel = int(dust-'0');
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("dustLv: ");
    lcd.print(dustLevel);
    Serial.print("dust:");
    Serial.println(dustLevel);
    
    char humidity = Serial1.read();
    humLevel = humidity - '0';
    lcd.setCursor(0,1);
    lcd.print("humLv:");
    lcd.print(humLevel);
    Serial.print("hum:");
    Serial.println(humLevel);
    
    char temp1, temp2;
    temp1 = Serial1.read();
    temp2 = Serial1.read();   
    temperature = (temp1-'0')*10 + (temp2-'0');
    lcd.setCursor(8,1);
    lcd.print("temp:");
    lcd.print(temperature);
    Serial.print("temp:");
    Serial.print(temp1);
    Serial.println(temp2);
       
  }
  window(temperature, humLevel, dustLevel); 
  
   /*
  if(isWinOpen==false){
    fanOn();
  }
  else if(isWinOpen==true){
    fanOff();
  } 
  */
}
