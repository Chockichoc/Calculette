#ifndef INTBUFFER_H
#define INTBUFFER_H

#include <Arduino.h>

struct IntBuffer {
    int32_t integer;
    int8_t exponent;

    IntBuffer() : integer{0}, exponent{0} {};
    IntBuffer(int32_t integer, int8_t exponent) : integer{integer}, exponent{exponent} {};
    uint8_t getLength();
};

#endif
