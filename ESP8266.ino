//DC : IvoW3D21NuKRE0AE
//id : nodemcu_controll
//
//username : scope

#define THINGER_SERIAL_DEBUG
//#include <DHT.h>
#include <dht.h>
#define sensor 5
#include <ThingerESP8266.h>
#include "arduino_secrets.h"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
#define relaydc 14
#define dht11 5 

//#define DHTTYPE DHT11
//
//DHT dht(dht11, DHTTYPE);
//float humidity, temprature;

dht DHT;
void setup() {

  DHT.read11(sensor);
//  float kelembaban = DHT.humidity;
//  float suhu = DHT.temperature;
//  float soil = 90;

  Serial.begin(115200);
  thing.add_wifi(SSID, SSID_PASSWORD);
  
//kontrol relay
  pinMode (relaydc, OUTPUT);
  digitalWrite (relaydc, 1);
  thing["relaydc"] << (digitalPin(relaydc));

//kirim data dht
  thing["dht11"] >> [](pson & out){
    out["humidity"] = DHT.humidity;
    out["temprature"] = DHT.temperature;
  };

}

void loop() {
  thing.handle();
  float kelembaban = DHT.temperature;
  Serial.println(kelembaban);
  delay(1000);
}
