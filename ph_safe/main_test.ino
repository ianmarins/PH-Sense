//ESSE CODIGO RODA NO ESP8266 
#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h> 
#include <Wire.h> 




String apiKey = "B6Y8YCA3W1EO3H0Z";       //trocar pela API Write
const char* server = "api.thingspeak.com";

#include<SoftwareSerial.h> //Included SoftwareSerial Library
#define WIFI_SSID       "Banhode1hora"
#define WIFI_PASSWORD   "5239asfalto"

int ph_pin = A0; //This is the pin number connected to Po
const char* ssid     = "lemes";           // REDE
const char* password = "10201020";           // REDE
//const char* ssid     = "Banhode1hora";           // REDE
//const char* password = "5239asfalto";           // REDE
int wifiStatus; 
WiFiClient client;

void setup() {
  Serial.begin(9600);
  Serial.println("         PH ");
  Serial.println("PROJETO GECO7AN | pH Sense");
 

 // Iniciar ligação à rede 
      Serial.println();
      Serial.println();
      Serial.print("A ligar à rede ");
      Serial.println(ssid);
 
      WiFi.begin(ssid, password);
 
      while (WiFi.status() != WL_CONNECTED)
      {
        delay(500);
        Serial.print(".");
      }


      //STATUS DA CONEXÃO DA REDE
       wifiStatus = WiFi.status();
 
      if(wifiStatus == WL_CONNECTED)
      {
         Serial.println("");
         Serial.println("O seu nodeMCU está ligado!");  
         Serial.print("Endereço IP: ");
         Serial.println(WiFi.localIP()); 
               
        
      }  
      else
      {
        Serial.println("");
        Serial.println("OPAAA DU RUIM...o seu nodeMCU não se consegue ligar...");
      }
      
      delay(1000);  

    
  
  }

void loop() {


 
  int measure = analogRead(ph_pin);
  Serial.print("Measure: ");
  Serial.print(measure);
   
 
  double voltage = 3 / 1024.0 * measure; //classic digital to voltage conversion
  Serial.print("\tVoltage: ");
  Serial.print(voltage, 3);

  // PH_step = (voltage@PH7 - voltage@PH4) / (PH7 - PH4)
  // PH_probe = PH7 - ((voltage@PH7 - voltage@probe) / PH_step)
  float Po = 7 + ((2.51 - voltage) / 0.18);     //float Po = 7 + ((2.598 - voltage) / 0.18);
  Serial.print("\tPH: ");
  Serial.print(Po, 3);

   
 //Inicia um client TCP para o envio dos dados
  if (client.connect(server,80)) {
    String postStr = apiKey;
           postStr +="&field1=";
           //postStr +="&amp;field1=";
           postStr += String(Po);
           postStr += "\r\n\r\n";
 
     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(postStr.length());
     client.print("\n\n");
     client.print(postStr);    


      delay(1000);

     Serial.println("");
     //Serial.print("ENVIADO: ");
    // Serial.print(Po);
    //Serial.println("");
   
  //Serial.print("Ph Enviado: ");
  //Serial.println(Firebase.getFloat("Ph"));



  //delay(1000);

  //delay(500);

  }
   client.stop();
  

}
