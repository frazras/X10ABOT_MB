/*
  X10ABOT_MB.h - Library for flashing X10ABOT_MB code.
  Created by Rohan A. Smith, January 31, 2012.
  Released into the public domain.
*/
#include <Wire.h>
//#include <Arduino.h> //"WProgram.h"
#include "X10ABOT_MB.h" //include the declaration for this class
#include <../X10ABOT_DB/X10ABOT_DB.h> //include the declaration for this class

X10ABOT_DB db(LOGGING);
//TwoWire Wire();
//TwoWire Wire = TwoWire();


//<<constructor>> setup the ...
X10ABOT_MB::X10ABOT_MB(byte logging){
  //pinMode(pin, OUTPUT);
  _logging = logging;

}

/*X10ABOT_MB::X10ABOT_MB(byte logging){
  //pinMode(pin, OUTPUT);
  _logging = logging;
}*/


//<<destructor>>
X10ABOT_MB::~X10ABOT_MB(){/*nothing to destruct*/}

/*Byte 1:1111XXXX FUNCTION BYTE
Byte 1:XXXX1111 OPERAND BYTE
Byte 2:11111111 D.B. SELECTION
Byte 3:X111111 PORT SELECTION
Byte 3:1XXXXXXX PIN SELECTION
Byte 3+n 11111111 DATA BYTES; n> 0*/



void X10ABOT_MB::dispatch(byte* pattern, byte byte_length){
  //Serial.write("pattern0: ");Serial.println(pattern[0], BIN);
  //Serial.write("DB address: ");Serial.println(pattern[1]);
  //Serial.write("pattern2: ");Serial.println(pattern[2]);
  //execute on the motherboard
  if (pattern[1]==0){
    /* TODO code */

    //Serial.println("motherboard");

    //Serial.println("localEvent: ");
    db.localEvent(pattern, byte_length);
    //Serial.println("end localEvent: ");
  }
  else{
   Wire.begin();
   //Serial.println("beginTransmission");
    Wire.beginTransmission(9); // transmit to device #x

    //Serial.println("write");

    Wire.write(pattern, byte_length);              // sends all bytes
    //Serial.println("ENDTransmission");

    i2cStatusLog(Wire.endTransmission());    // stop transmitting
    //Serial.println("OVERTransmission");
  }
}

void X10ABOT_MB::i2cStatusLog(byte var){
  if(_logging){
  switch (var) {
    case 0:
     Serial.println("I2C 0:success");
      break;
    case 1:
      Serial.println("I2C 1:data too long to fit in transmit buffer");
      break;
    case 2:
      Serial.println("I2C 2:received NACK on transmit of address");
      break;
    case 3:
      Serial.println("I2C 3:received NACK on transmit of data");
      break;
    case 4:
      Serial.println("I2C 4:other error");
      break;
    default:
      Serial.println("I2C 4:other error");
  }
}
}

void X10ABOT_MB::test_function(){
  //Serial.println("TEST FUNCTION");
  //Serial.println(OP_IO_HI, BIN);
  //Serial.print("Added: ");Serial.println((byte)(FN_IO+OP_IO_HI), BIN);
  byte test_pattern[] =   {FN_IO+OP_IO_HI,0,PORT_1+PIN_B,11}; //1-1(17)-9-1
  byte test_pattern2[] =  {FN_IO+OP_IO_LOW,0,PORT_1+PIN_B,8}; //1-2-9-2
  byte test_pattern3[] =  {FN_PWM+OP_NOP,0,PORT_1+PIN_B, 255*(20.0/100)}; //1-2-9-2
  byte test_pattern4[] =  {FN_PWM+OP_NOP,0,PORT_1+PIN_B, 255*(80.0/100)}; //1-2-9-2
  byte test_pattern6[] =  {FN_IO+OP_IO_LOW,9,PORT_1+PIN_B,8}; //1-2-9-2
  byte test_pattern7[] =   {FN_IO+OP_IO_HI,9,PORT_1+PIN_B,11}; //1-1(17)-9-1
//Serial.write("size:"); Serial.println(sizeof(test_pattern));
  dispatch(test_pattern, 3);
  dispatch(test_pattern7, 3);

  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) {
    // sets the value (range from 0 to 255):
    //Serial.write("fadeValue: "); Serial.println(sizeof(fadeValue));
    byte test_pattern5[] =  {FN_PWM+OP_NOP,0,PORT_1+PIN_B, fadeValue};
    byte test_pattern5a[] =  {FN_PWM+OP_NOP,9,PORT_1+PIN_B, fadeValue};
    //Serial.write("pre dispatch: ");
  dispatch(test_pattern5, 4);
  dispatch(test_pattern5a, 4);
  //Serial.write("post dispatch: ");
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
  //Serial.println("WAXOFF!");
  //delay(1000);
  dispatch(test_pattern2, 3);
  dispatch(test_pattern6, 3);
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) {
    // sets the value (range from 0 to 255):
    byte test_pattern5[] =  {FN_PWM+OP_NOP,0,PORT_1+PIN_B, fadeValue};
    byte test_pattern5a[] =  {FN_PWM+OP_NOP,9,PORT_1+PIN_B, fadeValue};
    dispatch(test_pattern5, 4);
    dispatch(test_pattern5a, 4);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
  //delay(1000);
  //Serial.println("WAXON!");
}
