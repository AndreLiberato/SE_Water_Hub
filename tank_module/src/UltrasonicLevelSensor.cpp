#include "UltrasonicLevelSensor.hpp"

// Construtor
UltrasonicLevelSensor::UltrasonicLevelSensor() { }

// Inicializa os pinos
void UltrasonicLevelSensor::begin()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

// Mede a distância usando o sensor ultrassônico
float UltrasonicLevelSensor::measureDistance()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    float distance = (duration * soundSpeed) / 2.0;
    return round(distance * 10.0f) / 10.0f;
}

// Retorna o nível atual no recipiente
float UltrasonicLevelSensor::getLevel()
{
    float distance = measureDistance();
    float level = tankHeight - distance + tankOffSet;
    return max(level, 0.0f);
}

// Retorna o percentual de preenchimento
float UltrasonicLevelSensor::getFillPercentage()
{
    float level = getLevel();
    float percentage = (level / tankHeight) * 100.0;
    return min(max(percentage, 0.0f), 100.0f);
}
