#include <SoftwareSerial.h>
SoftwareSerial s(D6, D5);

/*typedef union data {
  int value;
  byte buffer[4];
} Data; */

//Data data; 

char texto;

void setup() {
  //Serial Begin at 9600 Baud 
  Serial.begin(9600);
  s.begin(9600);
}

void loop() {
   
  if (Serial.available() > 0)
  {   
    //Serial.readBytes(data.buffer, sizeof(int)); //Read the serial data and store it
    //Serial.println(data.value);
    texto = s.read();
    Serial.println(texto);
    delay(1000);
  }
  
}
