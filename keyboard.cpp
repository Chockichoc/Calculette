#include "keyboard.h"
#include "arduino.h"



void Keyboard::scanInput(InputToScan input) {
  digitalWrite(row_A, (input & 0b00011) ? LOW : HIGH);
  digitalWrite(row_B, (input & 0b00101) ? LOW : HIGH);
  digitalWrite(row_C, (input & 0b01001) ? LOW : HIGH);
  digitalWrite(row_D, (input & 0b10001) ? LOW : HIGH);
}

uint32_t Keyboard::readInput() {
  uint32_t i = 0;
  scanInput(A);
  delay(2);

  i +=  (digitalRead(col_A) ? 0 :  1L<<0) + 
        (digitalRead(col_B) ? 0 :  1L<<1) + 
        (digitalRead(col_C) ? 0 :  1L<<2) +
        (digitalRead(col_D) ? 0 :  1L<<3) +
        (digitalRead(col_E) ? 0 :  1L<<4);

  scanInput(B);
  delay(2);
  
  i +=  (digitalRead(col_A) ? 0 :  1L<<5) + 
        (digitalRead(col_B) ? 0 :  1L<<6) + 
        (digitalRead(col_C) ? 0 :  1L<<7) +
        (digitalRead(col_D) ? 0 :  1L<<8);

  scanInput(C);
  delay(2);
  
  i +=  (digitalRead(col_A) ? 0 :  1L<<9) + 
        (digitalRead(col_B) ? 0 :  1L<<10) + 
        (digitalRead(col_C) ? 0 :  1L<<11) +
        (digitalRead(col_D) ? 0 :  1L<<12);

  scanInput(D);
  delay(2);
  
  i +=  (digitalRead(col_A) ? 0 :  1L<<13) + 
        (digitalRead(col_B) ? 0 :  1L<<14) + 
        (digitalRead(col_C) ? 0 :  1L<<15) +
        (digitalRead(col_D) ? 0 :  1L<<16);
  
  scanInput(idle);

  return i;
}
