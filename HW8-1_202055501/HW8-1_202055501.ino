byte patterns[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xE6};
int digit_select_pin[]{66,67,68,69};
int segment_pin[]={58,59,60,61,62,63,64,65};
int SEGMENT_DELAY = 5;
unsigned long time_previous, time_current;
int minutes=0, seconds=0;
int button_pin = 14;
int numIncrease = 0;
int numDecrease = 999;
boolean buttonPressed = false;

void show_digit(int pos, int number){
  for(int i=0; i<3; i++){
    if(i+1==pos){
      digitalWrite(digit_select_pin[i],LOW);
    }
    else{
      digitalWrite(digit_select_pin[i],HIGH);
    }
    for(int i=0; i<8; i++){
      boolean on_off = bitRead(patterns[number],7-i);
      digitalWrite(segment_pin[i],on_off);
    }
  }
}

void show_3_digit(int number){
  number=number%1000;
  int hundreads=number/100;
  number=number%100;
  int tens=number/10;
  int ones=number%10;

  show_digit(1,hundreads);
  delay(SEGMENT_DELAY);
  show_digit(2,tens);
  delay(SEGMENT_DELAY);
  show_digit(3,ones);
  delay(SEGMENT_DELAY);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(button_pin,INPUT);
  for(int i=0;i<3;i++){
    pinMode(digit_select_pin[i],OUTPUT);
  }
  for(int i=0;i<8;i++){
    pinMode(segment_pin[i], OUTPUT);
  }
  time_previous = millis();
  Serial.begin(9600); 
}


void loop() {
  // put your main code here, to run repeatedly:
  
  time_current = millis();
  if(time_current - time_previous >=1000){
    time_previous=time_current;
    numIncrease++;
    if(numIncrease>999) numIncrease = 0;
    numDecrease--;
    if(numDecrease<0) numDecrease = 999;
  }
  //if the button is not pressed
  if(digitalRead(button_pin)) buttonPressed = !buttonPressed;
  Serial.println(buttonPressed);
  if(buttonPressed == false){
    show_3_digit(numIncrease);
    numDecrease=999;
  }
  else{
    show_3_digit(numDecrease);
    numIncrease=0;
  }
  
}
