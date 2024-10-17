#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <MorseLaser.h>
#include <LiquidCrystal.h>

// ***** KONFIGURACJA SIECI WIFI *****
const char* ssid = "Nadajnik";  // Nazwa sieci WiFi
const char* password = "12345678";  // Hasło WiFi
WiFiServer server(80);  // Używamy serwera TCP na porcie 80

// ***** KONFIGURACJA TRANSMISJI MORSE'A *****
MorseLaser morse(LED_BUILTIN, 250);

// ***** KONFIGURACJA LCD *****
#define rs D2
#define en D3
#define d4 D1
#define d5 D5
#define d6 D6
#define d7 D7
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  // Uruchomienie servera w trybie Access Point
  Serial.begin(115200);
  WiFi.softAP(ssid, password);  // Tryb Access Point
  server.begin();
  Serial.println("Access Point started");
  
  // Wyświetlenie adresu IP Access Pointa
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  // LCD
  lcd.begin(16,2);
  lcd.setCursor(0,0);
}

void loop() {
  WiFiClient client = server.accept(); // Czekanie na klienta
  if (client) {
    Serial.println("Client connected");
    bool sendingMorse = false; // Flaga sygnalizująca, czy trwa wysyłanie Morse'a
    while (client.connected()) {
      if (client.available()) {
        String message = client.readStringUntil('\n'); // Odbieranie danych
        message.trim(); // Usunięcie białych znaków na końcu wiadomości
        Serial.println("Phone: " + message);
        lcd.clear();
        lcd.print(message);

        
        if (message == "start") {
          sendingMorse = true;
          Serial.println("Starting Morse transmission...");
        } else if (message == "stop") {
          sendingMorse = false;
          Serial.println("Stopping Morse transmission...");
        } else if (sendingMorse) {
          // Jeżeli transmisja jest aktywna, wysyłaj Morse'a
          Serial.println("Sending Morse for: " + message);
          morse.sendMorse(message); // Wyślij kod Morse'a dla wiadomości
        }
      }
    }
    client.stop(); // Zamykanie połączenia po rozłączeniu klienta
    Serial.println("Client disconnected");
  }
}


