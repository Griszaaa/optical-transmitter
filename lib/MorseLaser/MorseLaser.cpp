#include "MorseLaser.h"

// Tablica kodów Morse'a
const char* morseCode[] = {
  ".-",   // A
  "-...", // B
  "-.-.", // C
  "-..",  // D
  ".",    // E
  "..-.", // F
  "--.",  // G
  "....", // H
  "..",   // I
  ".---", // J
  "-.-",  // K
  ".-..", // L
  "--",   // M
  "-.",   // N
  "---",  // O
  ".--.", // P
  "--.-", // Q
  ".-.",  // R
  "...",  // S
  "-",    // T
  "..-",  // U
  "...-", // V
  ".--",  // W
  "-..-", // X
  "-.--", // Y
  "--..", // Z
  "-----",// 0
  ".----",// 1
  "..---",// 2
  "...--",// 3
  "....-",// 4
  ".....",// 5
  "-....",// 6
  "--...",// 7
  "---..",// 8
  "----." // 9
};

// Konstruktor inicjujący pin diody i długość kropki
MorseLaser::MorseLaser(int laserPin, unsigned int dotLength) {
  _laserPin = laserPin;
  _dotLength = dotLength;
  pinMode(_laserPin, OUTPUT);
  digitalWrite(_laserPin, LOW);  // Domyślnie dioda wyłączona
}

// Funkcja do wysyłania tekstu jako kod Morse'a
void MorseLaser::sendMorse(const String &text) {
  for (unsigned int i = 0; i < text.length(); i++) {
    sendChar(toupper(text[i]));  // Wysyłanie każdego znaku
    delay(_dotLength * 3);       // Przerwa między literami
  }
}

// Funkcja do ustawienia długości kropki
void MorseLaser::setDotLength(unsigned int length) {
  _dotLength = length;
}

// Funkcja do wysłania pojedynczej kropki
void MorseLaser::sendDot() {
  digitalWrite(_laserPin, HIGH);
  delay(_dotLength);
  digitalWrite(_laserPin, LOW);
  delay(_dotLength);  // Przerwa po kropce
}

// Funkcja do wysłania kreski
void MorseLaser::sendDash() {
  digitalWrite(_laserPin, HIGH);
  delay(_dotLength * 3);
  digitalWrite(_laserPin, LOW);
  delay(_dotLength);  // Przerwa po kresce
}

// Funkcja do wysyłania danego znaku
void MorseLaser::sendChar(char c) {
  if (c == ' ') {
    delay(_dotLength * 7);  // Przerwa dla spacji
    return;
  }

  if (c >= 'A' && c <= 'Z') {
    const char* morse = morseCode[c - 'A'];
    for (unsigned int i = 0; i < strlen(morse); i++) {
      if (morse[i] == '.') {
        sendDot();
      } else if (morse[i] == '-') {
        sendDash();
      }
    }
  } else if (c >= '0' && c <= '9') {
    const char* morse = morseCode[c - '0' + 26];
    for (unsigned int i = 0; i < strlen(morse); i++) {
      if (morse[i] == '.') {
        sendDot();
      } else if (morse[i] == '-') {
        sendDash();
      }
    }
  }
}
