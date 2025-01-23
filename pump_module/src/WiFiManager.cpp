#include "WiFiManager.hpp"

// Construtor
WiFiManager::WiFiManager() { }

// Inicializa e conecta ao Wi-Fi
void WiFiManager::begin() {
    WiFi.begin(ssid, password);
    Serial.println("Conectando ao Wi-Fi...");
    
    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startTime < timeout) { // Timeout de 30s
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWi-Fi conectado!");
        Serial.print("IP do dispositivo: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nFalha ao conectar ao Wi-Fi!");
    }
}
