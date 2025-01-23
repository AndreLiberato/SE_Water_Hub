#include "ValveControl.hpp"
#include <Arduino.h>

ValveControl::ValveControl() {}

void ValveControl::begin()
{
  pinMode(valvePin, OUTPUT);
  digitalWrite(valvePin, LOW);
}

void ValveControl::controlValve(String command)
{
  if (command == "on")
  {
    Serial.println("Ligando a válvula...");
    digitalWrite(valvePin, LOW);  // Válvula aberta
  }
  else if (command == "off")
  {
    Serial.println("Desligando a válvula...");
    digitalWrite(valvePin, HIGH); // Válvula fechada
  }
}

void ValveControl::valveCallback(char* topic, byte* payload, unsigned int length)
{
  if (strcmp(topic, "tank/1/valve") == 0)
  {
    String message = "";
    for (int i = 0; i < length; i++)
    {
      message += (char)payload[i];
    }

    controlValve(message);
  }
}
