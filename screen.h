#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <SPI.h>
#include "intBuffer.h"
#include "float64.h"

//Register Address Map
constexpr uint8_t NO_OP         = 0x00;
constexpr uint8_t DIGIT_0       = 0x01;
constexpr uint8_t DIGIT_1       = 0x02;
constexpr uint8_t DIGIT_2       = 0x03;
constexpr uint8_t DIGIT_3       = 0x04;
constexpr uint8_t DIGIT_4       = 0x05;
constexpr uint8_t DIGIT_5       = 0x06;
constexpr uint8_t DIGIT_6       = 0x07;
constexpr uint8_t DIGIT_7       = 0x08;
constexpr uint8_t DECODE_MODE   = 0x09;
constexpr uint8_t INTENSITY     = 0x0A;
constexpr uint8_t SCAN_LIMIT    = 0x0B;
constexpr uint8_t SHUTDOWN_MODE = 0x0C;
constexpr uint8_t DISPLAY_TEST  = 0x0F;

//Shudown
constexpr uint8_t TURNED_OFF    = 0x00;
constexpr uint8_t TURNED_ON     = 0x01;

//Decode Mode
constexpr uint8_t NO_DECODE     = 0x00;
constexpr uint8_t DECODE_0      = 0x01;
constexpr uint8_t DECODE_30     = 0x0F;
constexpr uint8_t DECODE_70     = 0xFF;

//Code B Font
constexpr uint8_t CHR_BAR       = 0x0A;
constexpr uint8_t CHR_E         = 0x0B;
constexpr uint8_t CHR_H         = 0x0C;
constexpr uint8_t CHR_L         = 0x0D;
constexpr uint8_t CHR_P         = 0x0E;
constexpr uint8_t CHR_BLANK     = 0x0F;
constexpr uint8_t CHR_DOT       = 0x80;

//Display Test Mode
constexpr uint8_t NORMAL_MODE   = 0x00;
constexpr uint8_t TEST_MODE     = 0x01;

class Screen {
  private:
    uint8_t cs;
    int8_t lightIntensity = 0x02;
 
  public:
    Screen(uint8_t cs): cs{cs} {   
      pinMode(cs, OUTPUT); 
      digitalWrite(cs, HIGH);
      SPI.begin();
      SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
    };

    void init();
    void writeData(uint8_t address, uint8_t data);
    void printInt(uint8_t integer, uint8_t digit);
    void printBuffer(IntBuffer buffer);
    void printError();

    void increaseLight();
    void decreaseLight();

    void launchIntro();

};

#endif
