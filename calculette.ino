#include "float64.h"
#include "keyboard.h"
#include "screen.h"
#include "intBuffer.h"


Keyboard keyboard{14, 15, 16, 17, 0, 1, 2, 3, 4};
Screen screen{10};

bool readFlag = false;
IntBuffer buffer;
Float64 lOperand{0};
Float64 rOperand{0};
uint8_t op{0};

void setup() {
  // init IRQ for Keyboard
  PCMSK2  = B00011111;
  PCIFR   = B00000000;
  PCICR   = B00000100;

  // init Screen
  screen.init();
  IntBuffer i{-123456, 5};
  screen.printBuffer(i);
}

void loop() {
  if(readFlag) 
  {
    readFlag = false;
  }
}




//Keyboard IRQ Handler
ISR(PCINT2_vect) {
  
    readFlag = true;

}
