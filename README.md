X10ABOT_MB
==========

Motherboard Library for the X10ABOT Robotic Platform
To test this library, run the example code below
Example code:
-------------
    //this should make the motherboard run its test function.
    #include <X10ABOT_MB.h>
    #include <Wire.h>
    #include <X10ABOT_DB.h>

    //ALLOW DEBUGGING over Serial
    #define LOGGING 0

    Actuator motor1(0,1);  //DC Motor
    //Sensor force(0,1);  //Force Sensor
    void setup(){
      Serial.begin(9600);
    }

    void loop(){
        motor1.on(100);
        //force.readAnalog();
        //int x = force.getAnalog();
        motor1.test_function();
    }
