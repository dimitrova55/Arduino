#include <Servo.h>

//connect buttons to digital pins 14, 15 through a pull-down resistor
//increase the angle of the servo motor by 10 degrees
//when the button connected to pin 14 is pressed
//decrease the angle by 10 degrees when the button connected to pin 15 is pressed

Servo myservo;
int servoPin = 11;
int buttonPin1 = 14, buttonPin2 = 15;
int angle = 0;
int angleStep = 10;
boolean isPressed1 = false, isPressed2 = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin1,INPUT);
  pinMode(buttonPin2,INPUT);
  myservo.attach(servoPin);
  myservo.write(angle);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(digitalRead(buttonPin1)) isPressed1 = !isPressed1;
  if(digitalRead(buttonPin2)) isPressed2 = !isPressed2;

  if (isPressed1){
    if(angle >= 180) angle = 180;
    else angle += angleStep;
    isPressed1 = !isPressed1;
    Serial.println("button1 is pressed and the angle is: " + String(angle));    
  }
  else if(isPressed2){
    if(angle <= 0) angle = 0;
    else angle -= angleStep;
    isPressed2 = !isPressed2;
    Serial.println("button2 is pressed and the angle is: " + String(angle));
  }
  myservo.write(angle);
  delay(500);

}
