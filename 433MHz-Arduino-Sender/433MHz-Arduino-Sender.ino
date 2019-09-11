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

    String cmdvalue  = Serial.readStringUntil(';');
    Serial.read(); //next character is semicolon, skip it
    String systemcode = Serial.readStringUntil(';');
    Serial.read();
    String unitcode  = Serial.readStringUntil('\0');

    if (cmdvalue == "ON") {
      mySwitch.switchOn(string2char(systemcode), string2char(unitcode));
      Serial.println("Switching on " + systemcode + " " + unitcode);
    } else if (cmdvalue == "OFF") {
      mySwitch.switchOff(string2char(systemcode), string2char(unitcode));
      Serial.println("Switching off " + systemcode + " " + unitcode);

    } else if (cmdvalue == "REV_ON") {
      mySwitch.switchOn('a', unitcode.toInt());
      Serial.println("Switching on " + systemcode + " " + unitcode);
    } else if (cmdvalue == "REV_OFF") {
      mySwitch.switchOff('a', unitcode.toInt());
      Serial.println("Switching off " + systemcode + " " + unitcode);

    } else if (cmdvalue == "Test") {
      Serial.println("I am up and running!");
    } else {
      Serial.println("Wrong command! Use ON or OFF.");
    }
  }
}

char* string2char(String command) {
  if (command.length() != 0) {
    char *p = const_cast<char*>(command.c_str());
    return p;
  }
}
