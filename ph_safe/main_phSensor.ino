#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>


#define FIREBASE_HOST 	"https://ph-safe.firebaseio.com/"  
#define FIREBASE_AUTH 	"2fxqpAHVPeqpfvNRA3VN3T6Yx61Zo53h9HDPjM4Q"
//#define WIFI_SSID 	  	"Banhode1hora"
//#define WIFI_PASSWORD 	"5239asfalto"

#define WIFI_SSID       "marins"
#define WIFI_PASSWORD   "10201020"



float phValue;
float Po;
int ph_pin = A0; //This is the pin number connected to Po


void setup() {

  Serial.begin(9600);
  Serial.println("         PH ");
  Serial.println("PROJETO GECO7AN | pH Sense");

   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);    
    delay(1000);  
  }
  Serial.println();
  Serial.print("Connected: ");
  Serial.println(WiFi.localIP());

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
  
            Firebase.pushFloat("ph", Po);
  
            if (Firebase.failed()) {
            Serial.println("   Falha no envio:");
            Serial.println(Firebase.error()); 
            delay(5000);
            }
            else 
            {
            Serial.print("\tPH: ");
            Serial.print(Po, 3);
  
            Serial.println("");
            delay(5000); // Espera 5 segundos
            }
}
