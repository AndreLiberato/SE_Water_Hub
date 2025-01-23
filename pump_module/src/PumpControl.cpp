#include "PumpControl.hpp"
#include <Arduino.h>

PumpControl::PumpControl(MqttManager &mqttManager)
    : mqttManager(mqttManager), pumpStatus(false),
      lastButtonState(HIGH), currentButtonState(HIGH),
      lastDebounceTime(0) {}

void PumpControl::begin()
{
    pinMode(relayPin, OUTPUT);
    pinMode(buttonPin, INPUT);
    digitalWrite(relayPin, HIGH);
}

void PumpControl::controlPump(String command)
{
    if (command == "on")
    {
        Serial.println("Acionando a bomba...");
        digitalWrite(relayPin, LOW); // Liga o relé (bomba)
        pumpStatus = true;
    }
    else if (command == "off")
    {
        Serial.println("Desligando a bomba...");
        digitalWrite(relayPin, HIGH); // Desliga o relé (bomba)
        pumpStatus = false;
    }
}

void PumpControl::buttonPressed()
{
    u_int8_t reading = digitalRead(buttonPin);
    // Verifica se o estado do botão mudou
    if (reading != lastButtonState)
    {
        // Reinicia o temporizador de debounce
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        // Se o estado do botão realmente mudou
        if (reading != currentButtonState)
        {
            currentButtonState = reading;
            if (currentButtonState == LOW)
            {
                // Toggle pump
                pumpStatus = !pumpStatus;

                String command = pumpStatus ? "on" : "off";
                controlPump(command);
                // Publica o novo estado no tópico MQTT
                char payload[4];
                command.toCharArray(payload, sizeof(payload));
                mqttManager.publishMessage("pump/1/status", payload);
                Serial.printf("Botão pressionado. Bomba %s.\n", pumpStatus ? "ligada" : "desligada");
            }
        }
    }

    lastButtonState = reading;
}

void PumpControl::pumpCallback(char *topic, byte *payload, unsigned int length)
{
    if (strcmp(topic, "pump/1/status") == 0)
    {
        String message = "";
        for (int i = 0; i < length; i++)
        {
            message += (char)payload[i];
        }

        // Controla a bomba de acordo com o comando recebido
        controlPump(message);
    }
}
