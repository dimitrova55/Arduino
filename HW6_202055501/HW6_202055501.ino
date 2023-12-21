int pin_LED1 = 2;
int pin_LED2 = 3;
unsigned long time_previous, time_current;
unsigned long time_previous2, time_current2;
unsigned long interval = 1000;
unsigned long interval2 = 1000;
boolean LED1_state = false;
boolean LED2_state = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(pin_LED1, OUTPUT);
  pinMode(pin_LED2, OUTPUT);
  digitalWrite(pin_LED1, LED1_state);
  digitalWrite(pin_LED2, LED2_state);
  Serial.begin(9600);
  time_previous = millis();
  time_previous2 = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  time_current = millis();
  time_current2 = millis();
  if(time_current - time_previous >= interval){
    Serial.print("Current interval is ");
    Serial.print(interval);
    Serial.print(" ms. ");
    Serial.println("time_previous: " + String(time_previous) + ",  time_current:  "+ String(time_current));
    time_previous = time_current;
    LED1_state= !LED1_state;
    //LED2_state= !LED2_state;
    digitalWrite(pin_LED1, LED1_state);
    //digitalWrite(pin_LED2, LED2_state);
  }
  if(time_current2 - time_previous2 >= interval2){
    time_previous2 = time_current2;
    LED2_state = !LED2_state;
    digitalWrite(pin_LED2, LED2_state);
  }
  int adc = analogRead(A0);
  // mapping to 0.5 ~ 1.5 sec interval
  interval = map(adc, 0, 1023, 500, 1500);
  interval2 = map(adc,0, 1023, 1500, 500);
}
