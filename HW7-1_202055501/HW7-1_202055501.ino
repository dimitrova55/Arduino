//photo-ressistor and LED
//control the number of LEDs turned on according to the amount of light
//turn on all 4 LEDs when it is darkest; 
//the darker it is the more LEDs must be turned on
//turn off all LEDs when it is brightest, under the value 150


int LED_pins[] = {2,3,4,5};
int resistor = 56;              //A2
int numLED = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(resistor, INPUT);
  for(int i=0; i<4; i++){
    pinMode(LED_pins[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int read_resistor = analogRead(resistor);
  //float voltage = read_resistor * 5.0/1024.0;
  Serial.println(String("resistor value: ") + read_resistor);// + String("voltage: ") + voltage);
  if(read_resistor <= 150) numLED = 0;                               //all LEDs off
  else if(read_resistor >150 && read_resistor <=368) numLED = 1;     //one LED on
  else if(read_resistor >369 && read_resistor <=586) numLED = 2;     //two LEDs on
  else if(read_resistor >587 && read_resistor <=804) numLED = 3;     //three LEDs on
  else if(read_resistor >805 && read_resistor <= 1023) numLED = 4;   //all LEDs on

  // turning LEDs on
  for(int i=0; i<numLED; i++){
    digitalWrite(LED_pins[i],HIGH);
  }

  //turning LEDs off
  for(int i=numLED; i<4; i++){
    digitalWrite(LED_pins[i],LOW);
  }
}
