#include "float64.h"
#include "keyboard.h"
#include "screen.h"
#include "intBuffer.h"

 enum : uint8_t {
  NOOP,
  ADD,
  SUB,
  MUL,
  DIV
};

Keyboard keyboard{14, 15, 16, 17, 0, 1, 2, 3, 4};
Screen screen{10};

bool readFlag = false;
IntBuffer buffer{0, 0};
Float64 lOperand{0};
Float64 rOperand{0};
Float64 result{0};
uint8_t op{NOOP};
bool isFloatNumber = false;

void setup() {
  // init IRQ for Keyboard
  PCMSK2  = B00011111;
  PCIFR   = B00000000;
  PCICR   = B00000100;

  // init Screen
  screen.init();  
  screen.printBuffer(buffer);
}

void loop() {
  if(readFlag) 
  {
    manageInput();
    readFlag = false;
  }
}

void addNumberToBuffer(uint8_t input) {
    if(buffer.integer < 10000000) {
      if(!(buffer.integer == 0  && buffer.exponent == 0 && input == 0 && isFloatNumber == false))
      {
      buffer.integer *= 10;
      buffer.integer += input;
      buffer.exponent += isFloatNumber ? (buffer.integer == 0 ? -1 : 0) : 1;
      }
      screen.printBuffer(buffer);
    }
    
}

void performOperation(uint8_t operation) {
      if(result.getSign() == 0 && result.getExponent() == 0 && result.getMantissa() == 0)
        lOperand = Float64{buffer.integer, buffer.exponent};
      else
        lOperand = result;
      buffer.integer = 0;
      buffer.exponent = 0;
      isFloatNumber = false;
      op = operation;
}

void manageInput() {
  uint32_t input = keyboard.readInput();
  switch(input) {
    case(1):
      buffer.integer = 0;
      buffer.exponent = 0;
      lOperand = Float64{0};
      rOperand = Float64{0};
      result = Float64{0};
      op = NOOP;
      isFloatNumber = false;
      screen.printBuffer(buffer);
    break;

    case(2):
      performOperation(DIV);
    break;

    case(4):
      performOperation(MUL);
    break;

    case(8):
      performOperation(SUB);
    break;

    case(16):
      addNumberToBuffer(7);
    break;

    case(32):
      addNumberToBuffer(8);
    break;

    case(64):
      addNumberToBuffer(9);
    break;

    case(128):
      addNumberToBuffer(4);
    break;

    case(256):
      addNumberToBuffer(5);
    break;

    case(512):
      addNumberToBuffer(6);
    break;

    case(1024):
      addNumberToBuffer(1);
    break;

    case(2048):
      addNumberToBuffer(2);
    break;

    case(4096):
      addNumberToBuffer(3);
    break;

    case(8192):
      isFloatNumber = true;
    break;

    case(16384):
      addNumberToBuffer(0);
    break;

    case(32768):
      rOperand = Float64{buffer.integer, buffer.exponent};
      
      switch(op){
        case 1:
          result = lOperand+rOperand;
        break;

        case 2:
          result = lOperand-rOperand;
        break;

        case 4:
          result = lOperand/rOperand;
        break;

        case 3:
          result = lOperand*rOperand;
        break;

        default:
        break;
      }
      lOperand = Float64{result};
      screen.printBuffer(IntBuffer{result});
    break;

    case(65536):
      performOperation(ADD);
    break;

    default:
    break;
  }

}


//Keyboard IRQ Handler
ISR(PCINT2_vect) {
  
    readFlag = true;

}
