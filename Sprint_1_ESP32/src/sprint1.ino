#define DHTPIN 4
#define TRIG_PIN 5
#define ECHO_PIN 18

#include "DHTesp.h"

DHTesp dht;

String contexto = "CAMPO";
int idEquipamento = 101;

void setup() {

  Serial.begin(115200);

  dht.setup(DHTPIN, DHTesp::DHT22);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.println("======================================");
  Serial.println("   SISTEMA INDUSTRIAL - ESP32");
  Serial.println("======================================");
  Serial.println("COMANDOS:");
  Serial.println("1 -> CAMPO");
  Serial.println("2 -> TRANSPORTE");
  Serial.println("3 -> AREA CRITICA");
  Serial.println("======================================");
}

void loop() {

  if (Serial.available()) {

    char opcao = Serial.read();

    switch(opcao) {

      case '1':
        contexto = "CAMPO";
        break;

      case '2':
        contexto = "TRANSPORTE";
        break;

      case '3':
        contexto = "AREA CRITICA";
        break;
    }
  }

  TempAndHumidity dados = dht.getTempAndHumidity();

  float temperatura = dados.temperature;
  float umidade = dados.humidity;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duracao = pulseIn(ECHO_PIN, HIGH);

  float distancia = duracao * 0.034 / 2;

  String status;

  if (distancia < 20) {
    status = "ALERTA - OBSTACULO";
  }
  else {
    status = "OPERACAO NORMAL";
  }

  Serial.println();
  Serial.println("======================================");
  Serial.println("      MONITORAMENTO EM TEMPO REAL");
  Serial.println("======================================");

  Serial.print("ID EQUIPAMENTO : ");
  Serial.println(idEquipamento);

  Serial.print("CENARIO        : ");
  Serial.println(contexto);

  Serial.println("--------------------------------------");

  Serial.print("TEMPERATURA    : ");
  Serial.print(temperatura);
  Serial.println(" C");

  Serial.print("UMIDADE        : ");
  Serial.print(umidade);
  Serial.println(" %");

  Serial.print("DISTANCIA      : ");
  Serial.print(distancia);
  Serial.println(" cm");

  Serial.println("--------------------------------------");

  Serial.print("STATUS         : ");
  Serial.println(status);

  Serial.println("======================================");

  delay(2000);
}