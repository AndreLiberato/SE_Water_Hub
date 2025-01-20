#include "LevelLedIndicator.hpp"

// Construtor
LevelLedIndicator::LevelLedIndicator() { }

// Inicializa os pinos dos LEDs
void LevelLedIndicator::begin() {
    pinMode(lowLevelLedPin, OUTPUT);
    pinMode(midLevelLedPin, OUTPUT);
    pinMode(highLevelLedPin, OUTPUT);
    turnOffAll();  // Garante que todos os LEDs estejam inicialmente apagados
}

// Desliga todos os LEDs
void LevelLedIndicator::turnOffAll() {
    digitalWrite(lowLevelLedPin, LOW);
    digitalWrite(midLevelLedPin, LOW);
    digitalWrite(highLevelLedPin, LOW);
}

// Atualiza os LEDs com base na porcentagem do nível
void LevelLedIndicator::update(float levelPercentage) {
    turnOffAll();  // Apaga todos os LEDs antes de acender o correspondente

    if (levelPercentage <= 40.0f) {
        digitalWrite(lowLevelLedPin, HIGH);  // Acende o LED de nível baixo
    } else if (levelPercentage > 40.0f && levelPercentage <= 70.0f) {
        digitalWrite(lowLevelLedPin, HIGH);  // Acende o LED de nível baixo
        digitalWrite(midLevelLedPin, HIGH);  // Acende o LED de nível médio
    } else if (levelPercentage > 70.0f) {
        digitalWrite(lowLevelLedPin, HIGH);  // Acende o LED de nível baixo
        digitalWrite(midLevelLedPin, HIGH);  // Acende o LED de nível médio
        digitalWrite(highLevelLedPin, HIGH); // Acende o LED de nível alto
    }
}
