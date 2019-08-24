#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <Ticker.h>
#include<SoftwareSerial.h> //Included SoftwareSerial Library

#define FIREBASE_HOST 	"ph-safe.firebaseio.com"
#define FIREBASE_AUTH 	"2fxqpAHVPeqpfvNRA3VN3T6Yx61Zo53h9HDPjM4Q"
#define WIFI_SSID 	  	"Banhode1hora"
#define WIFI_PASSWORD 	"5239asfalto"
#define PH_PIN A0
#define PUBLISHING_TIME 1000*60*30				// Sends the pH value to Firebase every 30 minutes


//WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP, "south-america.pool.ntp.org", utcOffsetInSeconds);
Ticker timer;
//JsonObject& json;

const long utcOffsetInSeconds = 3600;

float phValue;
bool publishNewValue;

int ph_pin = A0; //This is the pin number connected to Po

void publish() {
	publishNewValue = true;
}

void unpublish() {
	publishNewValue = false;
}

void setupPins() {
	pinMode(PH_PIN, INPUT);
}

void setupWifi() {
	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
	Serial.print("Connecting...");
	while (WiFi.status() != WL_CONNECTED) {
		Serial.print(".");
		delay(500);
	}
	Serial.println();
	Serial.print("Connected: ");
	Serial.println(WiFi.localIP());
}

void setupTimeClient() {
	//timeClient.begin();
}

void setupFirebase() {
	Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void init() {
	publishNewValue = true;
	phValue = 0.0;
}

float getDataFromPHSensor() {
  
	float valueFromSensor = 0;	
	
	// Calculate pH value... Paste pH code here!

 // int ph_pin = A0; //PINO TROXCAS DE DADOS
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

  Serial.println("");
  
  valueFromSensor = Po;


  delay(1000);  
	
	if (!isnan(valueFromSensor) || phValue == -1.0) {
		return valueFromSensor;
	}	
	return valueFromSensor;
}

char* getDate() {
	//return = timeClient.getDay() + "/" + timeClient.getMouth() + "/" + timeClient.getYear();	
}

char* getTime() {
	//return timeClient.getFormattedTime();
}

void mountJsonStructure() {
	StaticJsonBuffer<200> jsonBuffer;
	//json = jsonBuffer.createObject();
	json["valor"] = phValue;
	json["data"] = getDate();
	json["hora"] = getTime();
}

void sendToFirebase() {	
	Firebase.push("ph", phValue);
}

void setup() {
	Serial.begin(9600);
	setupPins();
	setupWifi();
	setupTimeClient();
	setupFirebase();
	init();
	
	timer.attach_ms(PUBLISHING_TIME, publish);

  Serial.println("         PH ");
  Serial.println("PROJETO GECO7AN | pH Sense");
}

void loop() {
  float phValue;
	//timeClient.update();
	if (publishNewValue) {
		phValue = getDataFromPHSensor();
		if (!isnan(phValue) || phValue >= 0.0)) {
			Serial.println("Publishing new pH value: " + phValue);			
			mountJsonStructure();
			sendToFirebase();
			unpublish();
		} else {
			Serial.println("Failed to read from pH sensor!");
		}
	}
	delay(200);
}
