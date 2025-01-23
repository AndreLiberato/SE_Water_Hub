#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>

class WiFiManager
{
private:
    static constexpr const char* ssid = "Sena_Network";        // SSID da rede Wi-Fi
    static constexpr const char* password = "Caibalion2023";   // Senha da rede Wi-Fi
    static constexpr unsigned int timeout = 30000;              // Tempo de timeout
public:
    // Construtor
    WiFiManager();

    // Inicializa o wifi
    void begin();
};

#endif
