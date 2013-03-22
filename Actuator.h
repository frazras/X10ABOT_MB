#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "X10ABOT_MB.h"

class Actuator: public X10ABOT_MB
{

  public:
    Actuator(byte db_address, byte port_number):X10ABOT_MB(0){
      _db = db_address;
      _port = port_number;
    }
    //Actuator(byte db_address, byte port_number, byte pin_select);
    ~Actuator();

    void run(byte power);
    void stop();
    void on(byte power);
    void on_a(byte power);
    void on_b(byte power);
    void off();
    void off_a();
    void off_b();

  private:
    byte _db, _port, _pin;
};

#endif
