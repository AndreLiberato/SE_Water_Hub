#include <Arduino.h>
#include <UltrasonicLevelSensor.hpp>
#include <LevelLedIndicator.hpp>
#include <WiFiManager.hpp>
#include <MqttManager.hpp>
#include <ValveControl.hpp>

MqttManager mqttManager;
UltrasonicLevelSensor levelSensor;
LevelLedIndicator levelIndicator;
ValveControl valveControl;

float lastLevelPercentage = -1.0;
unsigned long lastUpdateTime = 0;

void mqttCallback(char *topic, byte *payload, unsigned int length)
{
  valveControl.valveCallback(topic, payload, length);
}

void setup()
{
  Serial.begin(115200);
  WiFiManager wifiManager;
  wifiManager.begin();

  levelSensor.begin();
  levelIndicator.begin();
  valveControl.begin();

  mqttManager.setCallback(mqttCallback);

  mqttManager.begin();
}

void loop()
{
  if (!mqttManager.isConnected())
  {
    Serial.print("MQTT desconectado. Código de estado: ");
    Serial.println(mqttManager.getState());
    mqttManager.begin();
  }
  mqttManager.loop();

  unsigned long currentMillis = millis();
  if (currentMillis - lastUpdateTime >= 500)
  {
    lastUpdateTime = currentMillis;

    float levelPercentage = levelSensor.getFillPercentage();

    if (abs(levelPercentage - lastLevelPercentage) >= 0.2)
    {
      Serial.print("Percentual de preenchimento: ");
      Serial.print(levelPercentage);
      Serial.println(" %");

      levelIndicator.update(levelPercentage);

      char payload[10];
      dtostrf(levelPercentage, 1, 1, payload);

      mqttManager.publishMessage("tank/1/level", payload);
      lastLevelPercentage = levelPercentage;
    }
  }
}
