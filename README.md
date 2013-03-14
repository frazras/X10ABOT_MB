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

    X10ABOT_MB bot(LOGGING);
    void setup(){
      Serial.begin(9600);
    }

    void loop(){
      bot.test_function();
    }
