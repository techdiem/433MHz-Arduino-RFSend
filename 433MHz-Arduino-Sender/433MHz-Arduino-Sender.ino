#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
    mySwitch.enableTransmit(10); //Pin D10 on my chinese Nano
    mySwitch.setPulseLength(360);
    Serial.begin(9600);
}

void loop() {

    //send data only when it receives data:
    if (Serial.available() > 0) {

        //Read command and system-/unitcode from serial
        String cmdvalue  = Serial.readStringUntil(';');
        String systemcode; //for DIP
        char group; //for REV
        String unitcode; //for both

        if (cmdvalue == "ON" || cmdvalue == "OFF") {
            //10-DIP switches mode

            Serial.read(); //next character is semicolon, skip it
            systemcode = Serial.readStringUntil(';');
            Serial.read();
            unitcode = Serial.readStringUntil('\0');

        } else if (cmdvalue == "REV_ON" || cmdvalue == "REV_OFF") {
            //REV mode

            Serial.read(); //Semicolon
            systemcode = Serial.readStringUntil(';');
            //Convert the string to a char for the switchOn function in REV mode
            //it is kind of ugly
            if (systemcode == "A") {
                group = 'a';
            } else if (systemcode == "B") {
                group = 'b';
            } else if (systemcode == "C") {
                group = 'c';
            } else {
                group = 'd';
            }

            Serial.read();
            unitcode = Serial.readStringUntil('\0');
        }

        //10-DIP switches plug
        if (cmdvalue == "ON") {
            mySwitch.switchOn(string2char(systemcode), string2char(unitcode));
            Serial.println("Switching on " + systemcode + " " + unitcode);
        } else if (cmdvalue == "OFF") {
            mySwitch.switchOff(string2char(systemcode), string2char(unitcode));
            Serial.println("Switching off " + systemcode + " " + unitcode);

        //REV plug
        } else if (cmdvalue == "REV_ON") {
            mySwitch.switchOn(group, unitcode.toInt());
            Serial.println("Switching on " + systemcode + " " + unitcode);
        } else if (cmdvalue == "REV_OFF") {
            mySwitch.switchOff(group, unitcode.toInt());
            Serial.println("Switching off " + systemcode + " " + unitcode);

        } else if (cmdvalue == "Test") {
            Serial.println("I am up and running!");
        } else {
            Serial.println("Wrong command! Use ON/OFF for DIP switch power plugs or REV_ON/REV_OFF for the Rev ones.");
        }
  }
}

char* string2char(String command) {
  if (command.length() != 0) {
    char *p = const_cast<char*>(command.c_str());
    return p;
  }
}
