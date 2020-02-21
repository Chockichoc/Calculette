#include "intBuffer.h"

uint8_t countDigit(uint64_t n) ;
uint64_t power(uint64_t a, uint8_t b);

uint8_t IntBuffer::getLength() {
  uint8_t count = 0;
  int32_t _integer = this->integer;
  while (_integer != 0) { 
    _integer = _integer / 10; 
    ++count; 
  } 
  return count; 
}

IntBuffer::IntBuffer(Float64 fl64) {

  if(fl64.getMantissa() == 0 && fl64.getExponent() == 0 && fl64.getSign() == 0) {
    this->exponent = 0;
    this->integer = 0;
    return;
  }
  
  uint64_t integerPart = 0;
  float fractionalPart = 0.0f;
  
  uint64_t mantissa = fl64.getMantissa() + ((uint64_t)1<<52);
  int16_t exponent = fl64.getExponent() - 1023;
  uint8_t sign = fl64.getSign();

  for(int8_t i = 0; i < 53; i++) {
    if((exponent - i) >= 0) 
      integerPart += (mantissa & ((uint64_t)1<<(52-i))) ? power(2, exponent-i) : 0.0f;
    else
      fractionalPart += (mantissa & ((uint64_t)1<<(52-i))) ? 1.0f / power(2, -(exponent-i)) : 0.0f;
  }

  uint8_t delta = (sign == 0 ? 8 : 7) - max(1, countDigit(integerPart));
  uint64_t roundedFractionalPart = round(fractionalPart * power(10, delta));
  int8_t ex = (integerPart != 0) ? countDigit(integerPart) : -(delta - countDigit(roundedFractionalPart));

  
  if(roundedFractionalPart != 0) {
    uint8_t count = countDigit(roundedFractionalPart);
    for(uint8_t i = 0; i < count; i++) {
      if(roundedFractionalPart % 10 == 0) {
        delta--;
        roundedFractionalPart = roundedFractionalPart / 10;
      }
    }
    integerPart *= power(10, delta);
  }

  this->exponent = (int8_t)ex;
  this->integer = (int32_t)((sign == 0 ? 1 : -1) * (integerPart + roundedFractionalPart));

}
