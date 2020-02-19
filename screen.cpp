#include "screen.h"

uint8_t countDigit(long long n) 
{ 
    uint8_t count = 0; 
    while (n != 0) { 
        n = n / 10; 
        ++count; 
    } 
    
    return count; 
} 

void Screen::writeData(uint8_t address, uint8_t data) {
  digitalWrite(cs, LOW);

  SPI.transfer(address); 
  SPI.transfer(data);  
  
  digitalWrite(cs, HIGH);
}


void Screen::printInt(uint8_t integer, uint8_t digit) {
  const static uint8_t index[8] = {DIGIT_4, DIGIT_5, DIGIT_6, DIGIT_7, DIGIT_0, DIGIT_1, DIGIT_2, DIGIT_3}; 
  writeData(index[digit], integer);
}

void Screen::printBuffer(IntBuffer buffer) {
  bool isPositive = buffer.integer > 0;
  if(isPositive) {
      
  } else {
    printInt(CHR_BAR, 0);
  }
  
  for(uint8_t i = 0; i < buffer.getLength(); i++) {
    
  }
}
