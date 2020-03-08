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
uint8_t op{ADD};
bool isFloatNumber = false;
bool canCompute = false;
bool isNewOperation = true;

void setup() {
  // init IRQ for Keyboard
  PCMSK2  = B00011111;
  PCIFR   = B00000000;
  PCICR   = B00000100;

  // init Screen
  screen.init();  
  screen.launchIntro();
  screen.printBuffer(buffer);
}

void loop() {
  if(readFlag) 
  {
    manageInput();
    readFlag = false;
  }
}

void reset() {
  buffer.integer = 0;
  buffer.exponent = 0;
  lOperand = Float64{0};
  rOperand = Float64{0};
  result = Float64{0};
  op = ADD;
  isFloatNumber = false;
  canCompute = false;
  isNewOperation = true;
}

void addNumberToBuffer(uint8_t input) {
    if(isNewOperation){
      reset();
      isNewOperation = false;
    }
    canCompute = true;
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

void performOperation() {
  if(canCompute) {
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
    if(result == Float64{0x7FFFFFFFFFFFFFFF} || result > Float64{0x4197D783FC000000} || result < Float64{0xC16312CFE0000000}){
      screen.printError();
      reset();
    }
    else {
      screen.printBuffer(IntBuffer{result});
      canCompute = false;
    }
  }
}

void chooseOperation(uint8_t operation) {
      isNewOperation = false;
      if(canCompute){
        performOperation();
        canCompute = false;
      }
      if(result.getSign() == 0 && result.getExponent() == 0 && result.getMantissa() == 0)
        lOperand = Float64{0, 0};
      else
        lOperand = result;
      buffer.integer = 0;
      buffer.exponent = 0;
      isFloatNumber = false;
      op = operation;
}

void manageInput() {
  uint64_t input = keyboard.readInput();
  switch(input) {
    case(1):
      reset();
      screen.printBuffer(buffer);
    break;

    case(2):
      chooseOperation(DIV);
    break;

    case(4):
      chooseOperation(MUL);
    break;

    case(8):
      chooseOperation(SUB);
    break;

    case(9):
      screen.decreaseLight();
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

    case(2049):
      screen.decreaseLight();
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
      canCompute = true;
      isNewOperation = true;
      performOperation();
    break;

    case(65536):
      chooseOperation(ADD);
    break;

    case(65537):
      screen.increaseLight();
    break;

    default:
    break;
  }

}


//Keyboard IRQ Handler
ISR(PCINT2_vect) {
  
    readFlag = true;

}
