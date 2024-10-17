#ifndef MorseLaser_h
#define MorseLaser_h

#include <Arduino.h>

class MorseLaser {
  public:
    MorseLaser(int laserPin, unsigned int dotLength = 250);
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
