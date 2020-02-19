#include "intBuffer.h"

uint8_t IntBuffer::getLength() {
  uint8_t count = 0;
  int32_t _integer = this->integer;
  while (_integer != 0) { 
    _integer = _integer / 10; 
    ++count; 
  } 
  return count; 
}
