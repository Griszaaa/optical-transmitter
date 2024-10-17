#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <MorseLaser.h>

// ***** KONFIGURACJA SIECI WIFI *****
const char* ssid = "Nadajnik";  // Nazwa sieci WiFi
const char* password = "12345678";  // Hasło WiFi
WiFiServer server(80);  // Używamy serwera TCP na porcie 80

// ***** KONFIGURACJA TRANSMISJI MORSE'A *****
MorseLaser morse(LED_BUILTIN,250);


void WiFiSetup();
void WiFiReceive();

void setup() {
  WiFiSetup();
}

void loop() {
  WiFiReceive();
}

void WiFiSetup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);  // Tryb Access Point
  server.begin();
  Serial.println("Access Point started");
  
  // Wyświetlenie adresu IP Access Pointa
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
}

void WiFiReceive() {
  WiFiClient client = server.accept(); // Czekanie na klienta
  if (client) {
    Serial.println("Client connected");

    while (client.connected()){
      if (client.available()) {
        String message = client.readStringUntil('\n'); // Odbieranie danych
        Serial.print("Received: ");
        Serial.println(message);  // Wyświetlanie otrzymanej wiadomości
      }
    }
    client.stop(); // Zamykanie połączenia po rozłączeniu klienta
    Serial.println("Client disconnected");
  }
}