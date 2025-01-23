#include <Arduino.h>
#include <WiFiManager.hpp>
#include <MqttManager.hpp>
#include <PumpControl.hpp>

MqttManager mqttManager;
PumpControl pumpControl(mqttManager);

void mqttCallback(char *topic, byte *payload, unsigned int length)
{
  pumpControl.pumpCallback(topic, payload, length);
}

void setup()
{
  Serial.begin(115200);
  WiFiManager wifiManager;
  wifiManager.begin();

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

  pumpControl.buttonPressed();
}
