#ifndef PUMPCONTROL_HPP
#define PUMPCONTROL_HPP

#include <Arduino.h>
#include <PubSubClient.h>
#include "MqttManager.hpp"

class PumpControl
{
private:
    static constexpr u_int8_t relayPin = 15;
    static constexpr u_int8_t buttonPin = 14;
    static constexpr u_int8_t debounceDelay = 50;
    u_int32_t lastDebounceTime;
    u_int8_t lastButtonState;
    u_int8_t currentButtonState;
    bool pumpStatus;
    MqttManager& mqttManager;

public:
    PumpControl(MqttManager& mqttManager);
    void begin();
    void controlPump(String command);
    void buttonPressed();
    void pumpCallback(char *topic, byte *payload, unsigned int length);
};

#endif
