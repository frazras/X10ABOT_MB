/**
 * X10ABOT_MB.h - Library for flashing X10ABOT_MB code.
 * Created by Rohan A. Smith, January 31, 2012.
 * Released into the public domain.
 *
 * Long description for class (if any)...
 *
 * @copyright  2006 Zend Technologies
 * @license    http://www.zend.com/license/3_0.txt   PHP License 3.0
 * @version    Release: @package_version@
 * @link       http://dev.zend.com/package/PackageName
 * @since      Class available since Release 1.2.0
 */

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


/**
 * X10ABOT_MB Constructor
 *
 * @param  byte logging  Toggles logging over Serial ON(1) OFF(0)
 */
X10ABOT_MB::X10ABOT_MB(byte logging){
  _logging = logging;
}

/**
 * X10ABOT_MB Dsstructor
 * no params
 */
X10ABOT_MB::~X10ABOT_MB(){
  /*nothing to destruct*/
}

/**
 * Dispatches microcode to the internal/external daughterboard for execution
 *
 * @param  byte*  microcode  This is an array of micricode instructions to be sent
 * @param  byte   byte_length the size in bytes of the microcode instruction
 * @return void
 */
void X10ABOT_MB::dispatch(byte* microcode, byte byte_length){
  if (microcode[1]==0){
    db.localEvent(microcode, byte_length);
  }
  else{
   Wire.begin();
    Wire.beginTransmission(microcode[1]); // transmit to device #x
    Wire.write(microcode, byte_length);              // sends all bytes
    i2cStatusLog(Wire.endTransmission());    // stop transmitting
  }
  //Serial.println(microcode[0], BIN);
  //Serial.println(microcode[1], BIN);
  //Serial.println(microcode[2], BIN);
  //Serial.println("---------------");
  //Serial.println(microcode[0]);
}

/**
* Byte 1:1111XXXX FUNCTION BYTE
* Byte 1:XXXX1111 OPERAND BYTE
* Byte 2:11111111 D.B. SELECTION
* Byte 3:1111111X PORT SELECTION
* Byte 3:XXXXXXX1 PIN SELECTION
* Byte 3+n 11111111 DATA BYTES; n> 0
*/

/**
 * Asserts a state to a Digital IO pin
 *
 * @param  byte  state  The state of the digital pin, HIGH(2), LOW(1), INPUT(0)
 * @param  byte  db_address The daughterboard address between 7 and 120, 0 for motherboard
 * @param  byte  port_number the daughter board's port number connected to the device
 * @param  byte  pin_select choose which of the I/O pins on the port to use A(0) or B(1)
 * @return void
 */
void X10ABOT_MB::digital(byte state, byte db_address, byte port_number, byte pin_select){
  byte microcode[] =   {FN_IO+state,db_address,((port_number-1)<<1)+pin_select};
  dispatch(microcode, sizeof(microcode));
}

/**
 * Asserts a PWM signal to a pin
 *
 * @param  byte  pwm_select choose which of the PWM pins on the port to use A(0) or B(1)
 * @param  byte  db_address The daughterboard address between 7 and 120, 0 for motherboard
 * @param  byte  port_number the daughter board's port number connected to the device
 * @param  byte  duty_cycle specify the duty cycle as a number between 0 and 255
 * @return void
 */
void X10ABOT_MB::pwm(byte pwm_select, byte db_address, byte port_number, byte duty_cycle){
  byte microcode[] =   {FN_PWM,db_address,((port_number-1)<<1)+pwm_select, duty_cycle};
  dispatch(microcode, sizeof(microcode));
}

/**
 * Monitors the stats of I2C transmissions
 *
 * @param  byte  var  Return status of Transmission
 * @return void
 */
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
