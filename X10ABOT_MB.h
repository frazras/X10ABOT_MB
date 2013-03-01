/*
  X10ABOT_MB.h - Library for flashing X10ABOT_MB code.
  Created by Rohan A. Smith, January 31, 2012.
  Released into the public domain.
*/


#ifndef X10ABOT_MB_H
#define X10ABOT_MB_H


#include "Arduino.h" //"WProgram.h"

//Functions
static const byte FN_IO = 1 << 4;
static const byte FN_PWM  = 2 << 4;
static const byte FN_SERIAL = 3 << 4;

//IO Operands
static const byte OP_IO_HI = 2;
static const byte OP_IO_LOW = 1;
static const byte OP_IO_INP = 0;

//NULL OPERATION
static const byte OP_NOP = 0;

//Ports 1 - 4
static const byte PORT_1 = 0 << 1;
static const byte PORT_2 = 1 << 1;
static const byte PORT_3 = 2 << 1;
static const byte PORT_4 = 3 << 1;

//Pins
static const byte PIN_A = 0;
static const byte PIN_B = 1;

class X10ABOT_MB {

  public:
    X10ABOT_MB(byte logging);
    //X10ABOT_MB(byte db_address, byte logging);
    ~X10ABOT_MB();

    void dispatch(byte* pattern, byte byte_length);
    void test_function();

    /**
    * Logging Functions
    **/
    void i2cStatusLog(byte var);

  private:
    int _logging;
    byte test_pattern[3];
    byte test_pattern2[3];

};

#endif
