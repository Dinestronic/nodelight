#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>





//-------------------------  MANDATORY  -----------------------------------

const char* ssid = "WiFi_Name";                                       //WiFi Name
const char* password = "WiFi_Password";                           //WiFi Password
String nodelight_id = "Controller_Key";               //Nodelight App Registered ID

//-------------------------------------------------------------------------




void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
 pinMode(D4, OUTPUT);
 pinMode(D1, OUTPUT); //Relay 1
 pinMode(D2, OUTPUT); //Relay 2
 pinMode(D3, OUTPUT); //Relay 3
 pinMode(D0, OUTPUT); //Relay 4
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(D4,HIGH);
    delay(500);
    digitalWrite(D4,LOW);
    Serial.println("Connecting...");
  }
  Serial.println("WiFi Connected!");
   digitalWrite(D4,LOW);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  
    http.begin("http://dinestronic.000webhostapp.com/nodelight/node_read.php?id="+nodelight_id);
    int httpCode = http.GET();                                                                 
    if (httpCode > 0) {
      const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonObject& root = jsonBuffer.parseObject(http.getString());

      if(root["status"] != "true"){

         Serial.println("This ID was not Registered. Please Regiser through NodeLight App...");
      }
      else{
        
    

      if(root["dev1"] == "1"){
          digitalWrite(D1,HIGH);
          Serial.print("Device 1:");
      Serial.println("ON");
      }
      else{
digitalWrite(D1,LOW);
        Serial.print("Device 1:");
      Serial.println("OFF");
      }
      
      if(root["dev2"] == "1"){
          digitalWrite(D2,HIGH);
          Serial.print("Device 2:");
      Serial.println("ON");
        
      }
      else{
digitalWrite(D2,LOW);
        Serial.print("Device 2:");
      Serial.println("OFF");
      }
      
      if(root["dev3"] == "1"){
          digitalWrite(D3,HIGH);
        Serial.print("Device 3:");
      Serial.println("ON");
      }
      else{
digitalWrite(D3,LOW);
        Serial.print("Device 3:");
      Serial.println("OFF");
      }
      
      if(root["dev4"] == "1"){
          digitalWrite(D0,HIGH);
        Serial.print("Device 4:");
      Serial.println("ON");
      }
      else{
digitalWrite(D0,LOW);
        Serial.print("Device 4:");
      Serial.println("OFF");
      }
      
      
    
     
      }

      
    }
    http.end();
  }
  delay(2000);
}
