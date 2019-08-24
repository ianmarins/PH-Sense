#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266wifi.h>
#include <Wire.h> 


int pHSense = A0;     //PH 

const char* ssid     = "Banhode1hora";         // REDE
const char* password = "5239asfalto";      // REDE
int wifiStatus;                              // REDE

 
void setup() {
 
  Serial.begin(9600);
    delay(100);
    Serial.println("PROJETO GECO7AN | pH Sense");
 /* 

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
 */ 
}


 
void loop(){

  

  //DAQUI PARA BAIXO É O CODIGO DE AJUSTE E MEDIÇÃO DO PH
    int measuringVal = analogRead(pHSense);
    Serial.print("Measuring Raw Value  >  ");
    Serial.print(measuringVal);
 
    double vltValue = 3.3/1024.0 * measuringVal;    //
    Serial.print("   Voltage Tensão Valor >    ");
    Serial.print(vltValue, 3);
 
    float P0 = 7 + ((2,7 - vltValue) / 0.11); //<< PRA CHEGAR NESSE ZERO 11 CALCULEI A PROPORCIONALIDADE  PARA 3.3 E COLOQUEI -0.09 E O -3.5PRO VALOR FICAR POSITIVO  ---- float P0 = -3.5 + ((1.65 - vltValue) / -0.11);
    //float A0 = P0 * 10;
    Serial.print("");
    Serial.print("  PH VALOR >> ");
    //Serial.println(A0, 3);
    Serial.println(P0, 3); 
    Serial.print("");
    delay(1000);  // PODEMOS POR UM DALAY MAIOR, ESTA 1000 APENAS PARA PODERMOS FAZER UMA MEDIA DEPOIS
}




//CODIGO PARA ADICIONAR FIREBASE    ---> ACESSAR  --> https://github.com/FirebaseExtended/firebase-arduino/tree/master/examples/FirebaseDemo_ESP8266
//Start Arduino
//Open File > Examples > FirebaseArduino > FirebaseRoom_ESP8266
//In FirebaseRoom_ESP8266: Replace WIFI_SSID and WIFI_PASSWORD with WiFi credentials
//Go to https://firebase.google.com/console/ and create a new Firebase Project
//Go to Database


/*
#include <ESP8266WiFi.h>

#include <FirebaseCloudMessaging.h>

// Set these to run example.
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"

#define SERVER_KEY "key_from_dashboard"
#define CLIENT_REGISTRATION_ID "key_from_client_after_registration"

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  FirebaseCloudMessaging fcm(SERVER_KEY);
  FirebaseCloudMessage message =
    FirebaseCloudMessage::SimpleNotification("Hello World!", "What's happening?");
  FirebaseError error = fcm.SendMessageToUser(CLIENT_REGISTRATION_ID, message);
  if (error) {
    Serial.print("Error:");
    Serial.print(error.code());
    Serial.print(" :: ");
    Serial.println(error.message().c_str());
  } else {
    Serial.println("Sent OK!");
  }
}

void loop() {
}


*/
