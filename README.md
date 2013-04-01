X10ABOT_MB
==========

Motherboard Library for the X10ABOT Robotic Platform
To test this library, run the example code below
Example code:
-------------
    #include <X10ABOT_MB.h>
    #include <X10ABOT_DB.h>
    #include <Wire.h>

    Actuator motor1(0,1);  //DC Motor, daughterboard 0, output port 1
    Sensor force(0,1);  //Analog Force Sensor, daughterboard 0, input port 1
    void setup(){
      Serial.begin(9600);
    }

    void loop(){
      motor1.on(100);
      Serial.println(force.getAnalog());
  }
