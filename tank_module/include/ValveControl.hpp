#ifndef VALVECONTROL_HPP
#define VALVECONTROL_HPP

#include <Arduino.h>

class ValveControl
{
private:
  static constexpr u_int8_t valvePin = 15;

public:
  ValveControl();
  void begin();
  void controlValve(String command);
  void valveCallback(char* topic, byte* payload, unsigned int length);
};

#endif
