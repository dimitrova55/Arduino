int i=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial1.available()){
    //char temp[5] = {};
    char temp;// = Serial1.read();
    temp = Serial1.read();
    if(i==5){
      i=0;
      Serial.println();
    }
    if(i==0){
      Serial.print("Current temperature is : ");
    }
    Serial.print(temp);
    i++;
      
    //}
 
//    //for(int i=0; i<5; i++){
//      temp = Serial1.read();
//    }


//    Serial.print("Current temperature is : ");
//    
//    Serial.println();
  }

}
