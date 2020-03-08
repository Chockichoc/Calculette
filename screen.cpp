#include "screen.h"

uint8_t countDigit(uint64_t n); 
uint64_t power(uint64_t a, uint8_t b);

void Screen::writeData(uint8_t address, uint8_t data) {
  digitalWrite(cs, LOW);

  SPI.transfer(address); 
  SPI.transfer(data);  
  
  digitalWrite(cs, HIGH);
}

void Screen::init() {
  writeData(DISPLAY_TEST, NORMAL_MODE);
  writeData(DIGIT_0, 0x00);
  writeData(DIGIT_1, 0x00);
  writeData(DIGIT_2, 0x00);
  writeData(DIGIT_3, 0x00);
  writeData(DIGIT_4, 0x00);
  writeData(DIGIT_5, 0x00);
  writeData(DIGIT_6, 0x00);
  writeData(DIGIT_7, 0x00);
  writeData(DECODE_MODE, NO_DECODE);
  writeData(INTENSITY, lightIntensity);
  writeData(SCAN_LIMIT, 0x07);
  writeData(SHUTDOWN_MODE, TURNED_ON);
}

void Screen::printInt(uint8_t integer, uint8_t digit) {
  const static uint8_t index[8] = {DIGIT_4, DIGIT_5, DIGIT_6, DIGIT_7, DIGIT_0, DIGIT_1, DIGIT_2, DIGIT_3}; 
  writeData(index[digit], integer);
}

void Screen::printError() {
  const static uint8_t error[8] = {0x00, 0x05, 0x1C, 0x4F, 0x05, 0x05, 0x4F, 0x00};
  writeData(DECODE_MODE, NO_DECODE);
  for(uint8_t i = 0; i < 8; i++) {
    printInt(error[i], i);
  }
}

void Screen::printBuffer(IntBuffer buffer) {
  writeData(DECODE_MODE, DECODE_70);
  uint8_t bufferLength = buffer.getLength();
  
  for(uint8_t i = 0; i < 8; i++) {
    if(i < bufferLength-min(0, buffer.exponent-1)) {
      printInt((abs(buffer.integer)/power(10, i)) % 10 + ((i!= 0) && (i == (bufferLength-buffer.exponent)) ? CHR_DOT : 0), i);
    } else if(i == bufferLength-min(0, buffer.exponent-1)) {
      printInt(buffer.integer < 0 ? CHR_BAR : CHR_BLANK, i);
    } else {
      printInt(CHR_BLANK, i);
    } 
  }
}

void Screen::increaseLight(){
  lightIntensity = min(15, lightIntensity + 1);
  writeData(INTENSITY, lightIntensity);
}

void Screen::decreaseLight(){
  lightIntensity = max(0, lightIntensity - 1);
  writeData(INTENSITY, lightIntensity);
}

void Screen::launchIntro(){
  uint8_t error[8*14]= {0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                        0x01, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                        0x40, 0x01, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
                        0x40, 0x40, 0x01, 0x08, 0x00, 0x00, 0x00, 0x00,
                        0x43, 0x40, 0x40, 0x01, 0x08, 0x00, 0x00, 0x00,
                        0x4F, 0x03, 0x40, 0x40, 0x01, 0x08, 0x00, 0x00,
                        0x4F, 0x0E, 0x23, 0x40, 0x40, 0x01, 0x08, 0x00,
                        0x4F, 0x0E, 0x3E, 0x63, 0x40, 0x40, 0x01, 0x08,
                        0x4F, 0x0E, 0x3E, 0x7E, 0x63, 0x40, 0x40, 0x01,
                        0x4F, 0x0E, 0x3E, 0x7E, 0x6F, 0x23, 0x40, 0x40,
                        0x4F, 0x0E, 0x3E, 0x7E, 0x67, 0x3E, 0x63, 0x40,
                        0x4F, 0x0E, 0x3E, 0x7E, 0x67, 0x3E, 0x7E, 0x63,
                        0x4F, 0x0E, 0x3E, 0x7E, 0x67, 0x3E, 0x7E, 0x6F,
                        0x4F, 0x0E, 0x3E, 0x7E, 0x67, 0x3E, 0x7E, 0x67};
  for(uint8_t i = 0; i < 14; i++){
    for(uint8_t j = 0; j < 8; j++){
      printInt(error[j + 8*i], j);
      delay(4);
    }
  }
  delay(800);
}
