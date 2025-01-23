#include "MqttManager.hpp"
#include <Arduino.h>

MqttManager::MqttManager() : client(espClient) {}

void MqttManager::begin()
{
    client.setServer(mqttServer, mqttPort);
    while (!client.connected())
    {
        Serial.print("Conectando ao MQTT...");
        if (client.connect(clientID, mqttUser, mqttPasswd))
        {
            Serial.println("Conectado!");
            subscribeToTopics();
        }
        else
        {
            Serial.print("Falha na conexão, código: ");
            Serial.println(client.state());
            delay(2000);
        }
    }
}

void MqttManager::loop()
{
    client.loop();
}

bool MqttManager::isConnected()
{
    return client.connected();
}
int MqttManager::getState()
{
    return client.state();
}

void MqttManager::subscribeToTopics()
{
    client.subscribe("tank/1/valve");
}

void MqttManager::publishMessage(const char *topic, const char *message)
{
    client.publish(topic, message);
}

void MqttManager::setCallback(MQTT_CALLBACK_SIGNATURE)
{
    client.setCallback(callback);
}
