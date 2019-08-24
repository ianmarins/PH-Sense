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

#include<SoftwareSerial.h> //Included SoftwareSerial Library
//#define FIREBASE_HOST  "ph-safe.firebaseio.com"
//#define FIREBASE_AUTH   "2fxqpAHVPeqpfvNRA3VN3T6Yx61Zo53h9HDPjM4Q"

#define FIREBASE_HOST  "teste-2c58a.firebaseio.com"
#define FIREBASE_AUTH   "N5f9nMxg36Ke6WsmTwgSvdfUDUZjCV1K0sWGGyAg" 

//2fxqpAHVPeqpfvNRA3VN3T6Yx61Zo53h9HDPjM4Q   antiga chave

#define WIFI_SSID       "Banhode1hora"
#define WIFI_PASSWORD   "5239asfalto"

int ph_pin = A0; //This is the pin number connected to Po
const char* ssid     = "Banhode1hora";           // REDE
const char* password = "5239asfalto";           // REDE
int wifiStatus;                                // REDE


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

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);     
  
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

  float pFire = Po;
  
  Firebase.pushFloat("Ph", pFire); // Envia o dado da variavel P0 PH
  //Firebase.setFloat("Ph", 50.27); // Envia o dado da variavel P0 PH
  

  Serial.println("");
  Serial.print("Ph Enviado: ");
  Serial.println(Firebase.getFloat("Ph"));



  //delay(1000);

  delay(1000);

  
}
