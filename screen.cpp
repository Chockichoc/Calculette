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
  writeData(DIGIT_0, 0x0F);
  writeData(DIGIT_1, 0x0F);
  writeData(DIGIT_2, 0x0F);
  writeData(DIGIT_3, 0x0F);
  writeData(DIGIT_4, 0x0F);
  writeData(DIGIT_5, 0x0F);
  writeData(DIGIT_6, 0x0F);
  writeData(DIGIT_7, 0x0F);
  writeData(DECODE_MODE, DECODE_70);
  writeData(INTENSITY, 0x02);
  writeData(SCAN_LIMIT, 0x07);
  writeData(SHUTDOWN_MODE, TURNED_ON);
}

void Screen::printInt(uint8_t integer, uint8_t digit) {
  const static uint8_t index[8] = {DIGIT_4, DIGIT_5, DIGIT_6, DIGIT_7, DIGIT_0, DIGIT_1, DIGIT_2, DIGIT_3}; 
  writeData(index[digit], integer);
}



void Screen::printBuffer(IntBuffer& buffer) {
  uint8_t bufferLength = buffer.getLength();
  
  for(uint8_t i = 0; i < 8; i++) {
    if(buffer.exponent >= 0) {
      if(i < bufferLength) {
        printInt((abs(buffer.integer)/power(10, i)) % 10 + ((i!= 0) && (i == (bufferLength-buffer.exponent-1)) ? CHR_DOT : 0), i);
      } else if(i == bufferLength) {
        printInt(buffer.integer < 0 ? CHR_BAR : CHR_BLANK, i);
      } else {
        printInt(CHR_BLANK, i);
      }
      
    }
  }
}
