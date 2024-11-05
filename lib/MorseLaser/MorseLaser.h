#ifndef MORSE_LASER_H
#define MORSE_LASER_H

#include <Arduino.h>

class MorseLaser {
public:
    MorseLaser(int laserPin, unsigned int dotLength = 50);
    void sendMorse(const String &text);
    void setDotLength(unsigned int length);
private:
    int _laserPin;
    unsigned int _dotLength;
    void sendDot();
    void sendDash();
    void sendChar(char c);
};

#endif
