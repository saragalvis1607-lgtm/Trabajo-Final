#include "DHT.h"

#define DHTPIN 4          
#define DHTTYPE DHT11


#define FAN_PIN 18      

DHT dht(DHTPIN, DHTTYPE);


const float TEMP_ON  = 27.0;  
const float TEMP_OFF = 26.50;  

bool fanState = false;         


const int pwmChannel = 0;
const int pwmFreq = 25000;     
const int pwmResolution = 8;   

void setup() {
  Serial.begin(115200);
  dht.begin();

  ledcAttach(FAN_PIN, pwmFreq, pwmResolution);

  ledcWrite(FAN_PIN, 0);

  Serial.println("Sistema iniciado...");
}

void loop() {

  float temperatura = dht.readTemperature();

  if (isnan(temperatura)) {
    Serial.println("Error leyendo DHT11");
    delay(2000);
    return;
  }

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");


  
  if (temperatura >= TEMP_ON && !fanState) {
    ledcWrite(FAN_PIN, 255);     
    fanState = true;

    Serial.println("Temperatura alta -> Ventilador ENCENDIDO");
  }

  else if (temperatura <= TEMP_OFF && fanState) {
    ledcWrite(FAN_PIN, 0);
    fanState = false;

    Serial.println("Temperatura estable -> Ventilador APAGADO");
  }

  
  if (fanState) {
    Serial.println("Ventilador funcionando...");
  } else {
    Serial.println("Ventilador apagado.");
  }

  Serial.println("----------------------");

  delay(2000);
}