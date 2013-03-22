#include "X10ABOT_MB.h"
/**
 * Sensor Constructor
 *
 * @param  byte db_address   Sets the  daughterboard's address
 * @param  byte port_number  Sets the  port_number on the daughterboard specified
 */
//Sensor::Sensor(byte db_address, byte port_number)

/**
 * Sensor Constructor
 *
 * @param  byte db_address  Sets the  daughterboard's address
 * @param  byte port_number  Sets the  port_number on the daughterboard specified
 * @param  byte port_number  Selects either pin A(0) or B(1) on the selected port
 */
/*Sensor::Sensor(byte db_address, byte port_number, byte pin_select){
    _db = db_address;
    _port = port_number;
    _pin = pin_select;
}
*/
/**
 * Sensor Destructor
 * no params
 */
Sensor::~Sensor(){
  /*nothing to destruct*/
}

X10ABOT_MB mb(LOGGING);

/**
 * Sensor readDigital
 *
 * @param  byte power  Drives the Sensor in the negative or positive direction based on the power level. It operates btween -100 and +100.
 */

 void Sensor::readDigital(){}
 void Sensor::readDigitalA(){}
 void Sensor::readDigitalB(){}
 void Sensor::readAnalog(){
  mb.analog(_db,_port);
}
int Sensor::getAnalog(){
  return mb.db._analog;
}
void Sensor::off(){}
