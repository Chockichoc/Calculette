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
  screen.writeData(DISPLAY_TEST, NORMAL_MODE);
  screen.writeData(DIGIT_0, 0x0F);
  screen.writeData(DIGIT_1, 0x0F);
  screen.writeData(DIGIT_2, 0x0F);
  screen.writeData(DIGIT_3, 0x0F);
  screen.writeData(DIGIT_4, 0x0F);
  screen.writeData(DIGIT_5, 0x0F);
  screen.writeData(DIGIT_6, 0x0F);
  screen.writeData(DIGIT_7, 0x0F);
  screen.writeData(DECODE_MODE, DECODE_70);
  screen.writeData(INTENSITY, 0x02);
  screen.writeData(SCAN_LIMIT, 0x07);
  screen.writeData(SHUTDOWN_MODE, TURNED_ON);

  screen.printBuffer(IntBuffer{1, 8});
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
