#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <arduino.h>

enum InputToScan : uint8_t {
  idle = 1,
  A = 1 << 1,
  B = 1 << 2,
  C = 1 << 3,
  D = 1 << 4
};

class Keyboard {
  private:
     uint8_t row_A, row_B, row_C, row_D;
     uint8_t col_A, col_B, col_C, col_D, col_E;
     void scanInput(InputToScan input);
     
  public:
    Keyboard(uint8_t row_A, uint8_t row_B, uint8_t row_C, uint8_t row_D, uint8_t col_A, uint8_t col_B, uint8_t col_C, uint8_t col_D, uint8_t col_E) :
      row_A{row_A}, row_B{row_B}, row_C{row_C}, row_D{row_D}, col_A{col_A}, col_B{col_B}, col_C{col_C}, col_D{col_D}, col_E{col_E} {
        pinMode(row_A, OUTPUT);
        pinMode(row_B, OUTPUT);
        pinMode(row_C, OUTPUT);
        pinMode(row_D, OUTPUT);
        pinMode(col_A, INPUT_PULLUP);
        pinMode(col_B, INPUT_PULLUP);
        pinMode(col_C, INPUT_PULLUP);
        pinMode(col_D, INPUT_PULLUP);
        pinMode(col_E, INPUT_PULLUP);

        digitalWrite(row_A, LOW);
        digitalWrite(row_B, LOW);
        digitalWrite(row_C, LOW);
        digitalWrite(row_D, LOW);
    };
    uint32_t readInput();
    
};

#endif
