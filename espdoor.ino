#include <RCSwitch.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "secrets.h"

RCSwitch radio = RCSwitch();

void lerSensorPorta(int valorLido){
  Serial.print("Valor Recebido: ");
  Serial.println(valorLido);
  byte estadoSensor = valorLido & 255;
  Serial.print("Valor Bits controle: ");
  Serial.println(estadoSensor);
  
    if (estadoSensor == 3){
      Blynk.notify("Door Opened");
    }

    if (estadoSensor == 9){
      Blynk.notify("Door Closed");
    }
  
}

void setup() {
  Serial.begin(9600);
  Serial.println("OK");
  pinMode(D4,OUTPUT);
  radio.enableReceive(D7);
  digitalWrite(D4,LOW);
 Blynk.begin(auth, ssid, pass);
}

void loop() {
  if (radio.available()){
    int valorLido = radio.getReceivedValue();
    lerSensorPorta(valorLido);
    radio.resetAvailable();
  }
  Blynk.run();
}
