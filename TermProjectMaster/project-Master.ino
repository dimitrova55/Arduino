#include <Adafruit_Sensor.h>

    #include <SoftwareSerial.h>
    #include <DHT.h>
    #include <DHT_U.h>
    
    #define DHTTYPE DHT11 // DHT 11
    SoftwareSerial mySerial(4,5);  //(18,19)
    
    int humidityPin = 2;
    int motionPin = 3;     //digitalRead;
    int measurePin =55;    // A1, dust sensor
    int ledPower = 6;      // dust sensore
    
    unsigned int time_prev, time_curr;
    unsigned int samplingTime = 280;
    unsigned int deltaTime = 40;
    unsigned int sleepTime = 9680;
    
    float voMeasured = 0;
    float calcVoltage = 0;
    float dustDensity = 0;

    char temp_to_send[3]={},dustLevel='0', humidityLevel='0';
    
    DHT dht(humidityPin, DHTTYPE);
    
    void setup() {
      
      // put your setup code here, to run once:
      mySerial.begin(9600);
      Serial.begin(9600);
      dht.begin();
      pinMode(ledPower,OUTPUT);
      pinMode(motionPin,INPUT);
      time_prev = millis();
    }
    
    void loop() {
      
      // put your main code here, to run repeatedly:
      time_curr = millis();
      if(time_curr - time_prev >= 500){
        
        time_prev = time_curr;
                  
        //fine dust sensor code
        digitalWrite(ledPower,LOW);
        delayMicroseconds(samplingTime);
        
        voMeasured = analogRead(measurePin);
        int tmp1 = map(voMeasured,0,1023,1,8);
        dustLevel = tmp1 + '0';
        
        delayMicroseconds(deltaTime);
        digitalWrite(ledPower,HIGH);
        delayMicroseconds(sleepTime);
         
        calcVoltage = voMeasured*(5.0/1024);
        dustDensity = 0.17*calcVoltage-0.1;
        
        if ( dustDensity < 0)
        {
          dustDensity = 0.00;
        }  
        //Serial.print("Raw Signal Value (0-1023):");
        //Serial.println(voMeasured);  
          Serial.print("Dust Density:");
        Serial.println(dustDensity);
        
        //humidity sensor code
        float humidityVal = dht.readHumidity();
        int tmp2 = map(humidityVal,0.0,100.0, 0,9);
        humidityLevel = tmp2+'0';
        
        // Reading temperature or humidity takes about 250 milliseconds!
        // Read temperature as Celsius (the default)
        float tempVal = dht.readTemperature();
        
        
        // Check if any reads failed and exit early (to try again).
        if (isnan(humidityVal) || isnan(tempVal)) {
           Serial.println("Failed to read from DHT sensor!");
          return;
        }
                 
        // Compute heat index in Celsius (isFahreheit = false)
        float hic = dht.computeHeatIndex(tempVal, humidityVal, false);
        Serial.print ("Humidity: ");
        Serial.print (humidityVal);
        Serial.print (" %\t");
        Serial.print ("Temperature: ");
        Serial.print (int(tempVal));
        Serial.print (" *C ");
        Serial.println();

        //sending data to Slave arduino       
        
        temp_to_send[0] = (int(tempVal)/10) + '0';
        temp_to_send[1] = (int(tempVal)%10) + '0';
        Serial.print("temp_to_send: ");
        Serial.print(temp_to_send[0]);
        Serial.println(temp_to_send[1]);
        mySerial.write(dustLevel);
        mySerial.write(humidityLevel);
        mySerial.write(temp_to_send[0]);
        mySerial.write(temp_to_send[1]);
        //delay(500);    
                  
      }
      
    }
