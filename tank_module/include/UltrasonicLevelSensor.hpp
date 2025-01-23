#ifndef ULTRASONIC_LEVEL_SENSOR_H
#define ULTRASONIC_LEVEL_SENSOR_H

#include <Arduino.h>

class UltrasonicLevelSensor
{
private:
    static constexpr u_int8_t trigPin = 4;               // Pino do TRIG
    static constexpr u_int8_t echoPin = 2;               // Pino do ECHO
    static constexpr float tankHeight = 50.0f;      // Altura máxima do reservatório (em cm)
    static constexpr float tankOffSet = 10.0f;      // Offset para ajuste na medição
    static constexpr float soundSpeed = 0.0343f;    // Velocidade do som no ar (em cm/us)
public:
    // Construtor
    UltrasonicLevelSensor();

    // Inicializa os pinos
    void begin();

    // Mede a distância usando o sensor ultrassônico
    float measureDistance();

    // Retorna o nível atual no recipiente
    float getLevel();

    // Retorna o percentual de preenchimento
    float getFillPercentage();
};

#endif
