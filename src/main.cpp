#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <MorseLaser.h>
#include <LiquidCrystal.h>

// ***** KONFIGURACJA SIECI WIFI *****
const char* ssid = "Nadajnik";  // Nazwa sieci WiFi
const char* password = "12345678";  // Hasło WiFi
WiFiServer server(80);  // Używamy serwera TCP na porcie 80

// ***** KONFIGURACJA TRANSMISJI MORSE'A *****
MorseLaser morseLaser(D1);
              
// ***** KONFIGURACJA LCD *****
#define rs D2
#define en D3
#define d4 D5
#define d5 D6
#define d6 D7
#define d7 D8
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// ***** ZMIENNE DO PRZEWIJANIA LCD *****
String messageToScroll = ""; // Przechowuje wiadomość do przewijania
unsigned int scrollIndex = 0; // Aktualny indeks przewijania
unsigned long previousMillis = 0; // Czas ostatniego przewinięcia
const long scrollInterval = 450; // Interwał przewijania (450 ms)

void setup() {
    // Uruchomienie servera w trybie Access Point
    WiFi.softAP(ssid, password);  // Tryb Access Point
    server.begin();

    // LCD
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.clear();

    // Wyświetlenie adresu IP Access Pointa
    lcd.print("IP: ");
    lcd.print(WiFi.softAPIP().toString().substring(0, 11));

    lcd.setCursor(0, 1);
    lcd.print("Port: ");
    lcd.print(server.port());
}

void scrollText() {
    unsigned long currentMillis = millis(); // Aktualny czas
    lcd.setCursor(0, 0);
    lcd.print("Message:");

    if(messageToScroll.length() <= 16) {
        lcd.setCursor(0, 1);
        lcd.print(messageToScroll); // Jeżeli tekst krótszy niż 16 znaków - wyświetl bez przewijania
    } 
    else if(currentMillis - previousMillis >= scrollInterval) { 
        previousMillis = currentMillis; // Zapisz czas przewinięcia
    
        lcd.setCursor(0, 1);
        // Wyświetlanie odpowiedniego fragmentu wiadomości
        lcd.print(messageToScroll.substring(scrollIndex, scrollIndex + 16)); 
    
        scrollIndex++; // Przesuwanie indeksu
        if(scrollIndex + 16 > messageToScroll.length()) {
        scrollIndex = 0; // Wracamy na początek po dotarciu do końca
    }
  }
}

void loop() {
    WiFiClient client = server.accept(); // Czekanie na klienta
    if(client) {
        lcd.clear();
        messageToScroll = "Connected";
        scrollText();
        bool sendingMorse = false; // Flaga sygnalizująca, czy trwa wysyłanie Morse'a
        morseLaser.laserOff();
        
    while(client.connected()) {
        if(client.available()) {
            String message = client.readStringUntil('\n'); // Odbieranie danych
            message.trim(); // Usunięcie białych znaków na końcu wiadomości

            // Wyczyszczenie LCD przed wyświetleniem nowej wiadomości
            lcd.clear();
            
            // Wyświetlanie wiadomości na LCD bez względu na transmisję Morse'a
            if(message != "start" || message != "stop") messageToScroll = message;
            scrollIndex = 0; // Zresetowanie indeksu przewijania
            scrollText(); // Wyświetlenie wiadomości na LCD

            if(message == "start") {

                sendingMorse = true;
                lcd.clear();  // Czyść LCD przed wyświetleniem nowej wiadomości
                messageToScroll = "Start Morse TX"; // Wyświetl komunikat o starcie
                morseLaser.sendMorse(message);

            } else if (message == "stop") {

                sendingMorse = false;
                lcd.clear();  // Czyść LCD przed wyświetleniem nowej wiadomości
                messageToScroll = "Stop Morse TX"; // Wyświetl komunikat o zatrzymaniu
                morseLaser.sendMorse(message);
          
            } else if (sendingMorse) {
                // Jeżeli transmisja jest aktywna, wysyłaj Morse'a
                morseLaser.sendMorse(message); // Wyślij kod Morse'a dla wiadomości
                delay(7*morseLaser.getDotLength());
            }
        }
      
        scrollText(); // Kontynuowanie przewijania tekstu na LCD
    }
    client.stop(); // Zamykanie połączenia po rozłączeniu klienta
    messageToScroll = "Disconnected";
    scrollText();
  }
}
