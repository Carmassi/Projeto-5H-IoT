#define BLYNK_TEMPLATE_ID "TMPLPqZFDryO"
#define BLYNK_DEVICE_NAME "ArdWIFI"
#define BLYNK_AUTH_TOKEN  "PN_crxoDIzwfQdNuKSFyw8G9kaJEr8c_"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "VIVOFIBRA-EFD1";
char pass[] = "smmfrid7qJ";

#define DHTPIN 2
#define RELE01 5
#define RELE02 4
#define RELE03 14
#define RELE04 12

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor(){
  float t = dht.readTemperature();
  if (isnan(t)){
    Serial.println("Sensor DTH não leu dados!");
    return;
  }
  Blynk.virtualWrite(V3, t);
}

void ligaluzsala(int sala){
  if(sala == 0){
    digitalWrite(RELE01, HIGH);
  }else{
    digitalWrite(RELE01, LOW);
  }
}

void ligaluzquarto(int quarto){
  if(quarto == 0){
    digitalWrite(RELE02, HIGH);
  }else{
    digitalWrite(RELE02, LOW);
  }
}

void ligaventilador(int vent){
  if(vent == 0){
    digitalWrite(RELE03, HIGH);
  }else{
    digitalWrite(RELE03, LOW);
  }
}

void setup(){
  pinMode(RELE01, OUTPUT);
  pinMode(RELE02, OUTPUT);
  pinMode(RELE03, OUTPUT);
  pinMode(RELE04, OUTPUT);
  pinMode(DHTPIN, INPUT);

  //inicia o relé inteiro desligado
  digitalWrite(RELE01, HIGH);
  digitalWrite(RELE02, HIGH);
  digitalWrite(RELE03, HIGH);
  digitalWrite(RELE04, HIGH);
  
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  dht.begin();

  timer.setInterval(1000L, sendSensor);
}

void loop(){
  Blynk.run();
  timer.run();
}

BLYNK_WRITE(V0){
  int sala = param.asInt();
  ligaluzsala(sala);
}

BLYNK_WRITE(V1){
  int quarto = param.asInt();
  ligaluzquarto(quarto);
}

BLYNK_WRITE(V2){
  int vent = param.asInt();
  ligaventilador(vent);
}