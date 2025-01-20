#include <Arduino.h>
#include <PubSubClient.h>
#include <UltrasonicLevelSensor.hpp>
#include <LevelLedIndicator.hpp>
#include <WiFiManager.hpp>

#define pinvalve 15
#define mqttserver "192.168.0.192"
#define mqttport 1883
#define mqttuser "wh"
#define mqttpasswd "Inter"

WiFiClient espClient;
PubSubClient client(espClient);
WiFiManager wifiManager;
UltrasonicLevelSensor levelSensor;
LevelLedIndicator levelIndicator;
float lastLevelPercentage = -1.0;

void mqttConnect()
{
  client.setServer(mqttserver, mqttport);
  while (!client.connected())
  {
    Serial.print("Conectando ao MQTT...");
    if (client.connect("tank_module", mqttuser, mqttpasswd))
    {
      Serial.println("Conectado!");
    }
    else
    {
      Serial.print("Falha na conexão, código: ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void setup()
{
  Serial.begin(115200);
  wifiManager.begin();
  levelSensor.begin();
  levelIndicator.begin();
  pinMode(pinvalve, OUTPUT);
  digitalWrite(pinvalve, HIGH);
  mqttConnect();
}

void loop()
{
  if (!client.connected())
  {
    Serial.print("MQTT desconectado. Código de estado: ");
    Serial.println(client.state());
    mqttConnect();
  }
  client.loop();

  float levelPercentage = levelSensor.getFillPercentage();

  if (abs(levelPercentage - lastLevelPercentage) >= 0.2)
  {
    Serial.print("Percentual de preenchimento: ");
    Serial.print(levelPercentage);
    Serial.println(" %");

    levelIndicator.update(levelPercentage);

    if (levelPercentage < 70)
    {
      Serial.println("Ligando o relé (válvula aberta)...");
      digitalWrite(pinvalve, LOW);
    }
    else
    {
      Serial.println("Desligando o relé (válvula fechada)...");
      digitalWrite(pinvalve, HIGH);
    }

    char payload[10];
    dtostrf(levelPercentage, 1, 1, payload);

    client.publish("tank/1/level", payload);
    lastLevelPercentage = levelPercentage;
  }

  delay(500);
}
