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
    "----.", // 9
    ".-.-.", // koniec wiadomosci '/'
    ".-.-.-", // . (kropka)
    "--..--", // , (przecinek)
    "..--..", // ? (znak zapytania)
    "-....-", // - (myślnik)
    ".-..-.", // " (cudzysłów)
    ".----.", // ' (apostrof)
    "-.--.", // ( (nawias otwierający)
    "-.--.-", // ) (nawias zamykający)
    "---...", // : (dwukropek)
    "-.-.--", // ! (wykrzyknik)
};

// Konstruktor inicjujący pin diody i długość kropki
MorseLaser::MorseLaser(int laserPin, unsigned int dotLength) {
    _laserPin = laserPin;
    _dotLength = dotLength;
    pinMode(_laserPin, OUTPUT);
    digitalWrite(_laserPin, HIGH);  // Domyślnie dioda włączona
}

// Funkcja do wysyłania tekstu jako kod Morse'a
void MorseLaser::sendMorse(const String &text) {
    for (unsigned int i = 0; i < text.length(); i++) {
        sendChar(text[i]); // Wysyłanie każdego znaku
        if (text[i] != ' ') {
            delay(_dotLength * 3); // Przerwa między literami
        }
    }
}

// Setter długości kropki
void MorseLaser::setDotLength(unsigned int length) {
    _dotLength = length;
}

// Getter czasu kropki
unsigned int MorseLaser::getDotLength() {
    return _dotLength;
}

// Funkcja do wyłączenia lasera
void MorseLaser::laserOff() {
    digitalWrite(_laserPin, LOW);
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
    
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        c = tolower(c);
        const char* morse = morseCode[c - 'a'];
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
    } else if (c == '/') {
        const char* morse = morseCode[36];
        for (unsigned int i = 0; i < strlen(morse); i++) {
            if (morse[i] == '.') {
                sendDot();
            } else if(morse[i] == '-') {
                sendDash();
            }
        }
    } else if (c == '.') {
        const char* morse = morseCode[37];
        for (unsigned int i = 0; i < strlen(morse); i++) {
            if (morse[i] == '.') {
                sendDot();
            } else if(morse[i] == '-') {
                sendDash();
            }
        }
    } else if (c == ',') {
        const char* morse = morseCode[38];
        for (unsigned int i = 0; i < strlen(morse); i++) {
            if (morse[i] == '.') {
                sendDot();
            } else if(morse[i] == '-') {
                sendDash();
            }
        }
    } else if (c == '?') {
        const char* morse = morseCode[39];
        for (unsigned int i = 0; i < strlen(morse); i++) {
            if (morse[i] == '.') {
                sendDot();
            } else if(morse[i] == '-') {
                sendDash();
            }
        }
    } else if (c == '-') {
        const char* morse = morseCode[40];
        for (unsigned int i = 0; i < strlen(morse); i++) {
            if (morse[i] == '.') {
                sendDot();
            } else if(morse[i] == '-') {
                sendDash();
            }
        }
    } else if (c == '"') {
        const char* morse = morseCode[41];
        for (unsigned int i = 0; i < strlen(morse); i++) {
            if (morse[i] == '.') {
                sendDot();
            } else if(morse[i] == '-') {
                sendDash();
            }
        }
    } else if (c == '\'') {
        const char* morse = morseCode[42];
        for (unsigned int i = 0; i < strlen(morse); i++) {
            if (morse[i] == '.') {
                sendDot();
            } else if(morse[i] == '-') {
                sendDash();
            }
        }
    } else if (c == '(') {
        const char* morse = morseCode[43];
        for (unsigned int i = 0; i < strlen(morse); i++) {
            if (morse[i] == '.') {
                sendDot();
            } else if(morse[i] == '-') {
                sendDash();
            }
        }
    } else if (c == ')') {
        const char* morse = morseCode[44];
        for (unsigned int i = 0; i < strlen(morse); i++) {
            if (morse[i] == '.') {
                sendDot();
            } else if(morse[i] == '-') {
                sendDash();
            }
        }
    } else if (c == ':') {
        const char* morse = morseCode[45];
        for (unsigned int i = 0; i < strlen(morse); i++) {
            if (morse[i] == '.') {
                sendDot();
            } else if(morse[i] == '-') {
                sendDash();
            }
        }
    } else if (c == '!') {
        const char* morse = morseCode[46];
        for (unsigned int i = 0; i < strlen(morse); i++) {
            if (morse[i] == '.') {
                sendDot();
            } else if(morse[i] == '-') {
                sendDash();
            }
        }
    }
}
