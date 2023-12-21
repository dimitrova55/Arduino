int pins_LED[] = {2,3,4,5};
int initial_value[] = {0,63,127,191};
int current_stage = 0;
int blink_stage[] = {0,0,0,0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i=0; i<4; i++){
    pinMode(pins_LED[i],OUTPUT);
    analogWrite(pins_LED[i],initial_value[i]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (current_stage >= 256) current_stage = 0;
  
  blink_stage[0] = current_stage + initial_value[0];
  Serial.print(String("blink_stage[0]") + blink_stage[0] + " ");  
  analogWrite(pins_LED[0],current_stage);
    
  if(current_stage+initial_value[1] >= 256){
    blink_stage[1] = current_stage+initial_value[1] - 256;
  } else{
    blink_stage[1] = current_stage+initial_value[1];
  }
  Serial.print(String("blink_stage[1]") + blink_stage[1] + " ");  
  analogWrite(pins_LED[1],blink_stage[1]);
  
  
  if(current_stage+initial_value[2] >= 256){
    blink_stage[2] = current_stage+initial_value[2] - 256;
  }else{
    blink_stage[2] = current_stage+initial_value[2];
  }
  Serial.print(String("blink_stage[2]" ) + blink_stage[2] + " ");  
  analogWrite(pins_LED[2], blink_stage[2]);
  
  
  if(current_stage+initial_value[3] >= 256){
    blink_stage[3] = current_stage+initial_value[3] - 256;
  }else{
    blink_stage[3] = current_stage+initial_value[3];
  }
  Serial.println(String("blink_stage[3]" ) + blink_stage[3] + " ");  
  analogWrite(pins_LED[3], blink_stage[3]);
  
  current_stage++;
  Serial.println();
}
