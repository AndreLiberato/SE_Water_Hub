#ifndef LEVEL_LED_INDICATOR_H
#define LEVEL_LED_INDICATOR_H

#include <Arduino.h>

class LevelLedIndicator {
private:
    static constexpr u_int8_t lowLevelLedPin = 21;    // Pino do LED de nível baixo
    static constexpr u_int8_t midLevelLedPin = 22;    // Pino do LED de nível médio
    static constexpr u_int8_t highLevelLedPin = 23;   // Pino do LED de nível alto

    void turnOffAll();  // Desliga todos os LEDs
public:
    // Construtor
    LevelLedIndicator();

    // Inicializa os pinos dos LEDs
    void begin();

    // Atualiza os LEDs com base na porcentagem do nível
    void update(float levelPercentage);
};

#endif // LEVEL_LED_INDICATOR_H
