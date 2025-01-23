#ifndef MQTTMANAGER_HPP
#define MQTTMANAGER_HPP

#include <PubSubClient.h>
#include <WiFi.h>

class MqttManager
{
private:
    WiFiClient espClient;
    PubSubClient client;
    static constexpr int mqttPort = 1883;
    static constexpr const char* mqttServer = "192.168.0.192";
    static constexpr const char* mqttUser = "wh";
    static constexpr const char* mqttPasswd = "Inter";
    static constexpr const char* clientID = "pump_module";

public:
    MqttManager();
    void begin();
    void loop();
    bool isConnected();
    int getState();
    void subscribeToTopics();
    void publishMessage(const char *topic, const char *message);
    void setCallback(MQTT_CALLBACK_SIGNATURE);
};

#endif
