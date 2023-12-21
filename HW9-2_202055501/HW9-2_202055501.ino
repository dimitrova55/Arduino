//connect a button to digital pin 14 and change the speed with every button press
//stop to rotate
//rotating with half of the max speed
//rotating with max speed

int Enable1 = 38;
int PWM1 = 9;
int DIR1 = 39;

int buttonPin = 14;
int speed = 0, count = 0;
boolean direction = true, isPressed=false;


void setup() {
  // put your setup code here, to run once:
  pinMode(Enable1, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(DIR1, OUTPUT);
  
  digitalWrite(Enable1, HIGH);
  digitalWrite(DIR1,HIGH);  //forward rotation
  digitalWrite(PWM1,!direction); //initial speed max
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(buttonPin) ){
    count++; 
    //isPressed = !isPressed;
    Serial.print("count=" + String(count));
  }
  if(count%3==0) 
  {
    speed = 0;    
  } 
  else if(count%3==1) {
    speed = 255;
  }
  else if(count%3==2){
    speed = 128;
  }
  Serial.println(" speed= " + String(speed));
  analogWrite(PWM1,speed);
  delay(500);
  
}
