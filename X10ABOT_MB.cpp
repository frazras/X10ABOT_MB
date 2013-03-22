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
#include "X10ABOT_MB.h" //include the declaration for this class
  #include <../X10ABOT_DB/X10ABOT_DB.h> //include the declaration for this class

X10ABOT_DB db(LOGGING);


/**
 * X10ABOT_MB Constructor
 *
 * @param  byte logging  Toggles logging over Serial ON(1) OFF(0)

X10ABOT_MB::X10ABOT_MB(byte logging){
  _logging = logging;
}
*/
/**
 * X10ABOT_MB Destructor
 * no params
 */
X10ABOT_MB::~X10ABOT_MB(){
  /*nothing to destruct*/
}

/**
 * Dispatches microcode to the internal/external daughterboard for execution
 *
 * @param  byte*  microcode  This is an array of microcode instructions to be sent
 * @param  byte   byte_length the size in bytes of the microcode instruction
 * @return void
 */
void X10ABOT_MB::dispatch(byte* microcode, byte byte_length){
  if (microcode[D_B_SELECTION]==0){
    db.localEvent(microcode, byte_length);
  }
  else{
   Wire.begin();
    Wire.beginTransmission(microcode[D_B_SELECTION]); // transmit to device #x
    Wire.write(microcode, byte_length);              // sends all bytes
    i2cStatusLog(Wire.endTransmission());    // stop transmitting
  }
  dispatchDataLog(microcode, sizeof(microcode));
}


