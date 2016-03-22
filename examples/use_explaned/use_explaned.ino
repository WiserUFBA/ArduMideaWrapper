#include <IRremote.h>
#include <MideaIR.h>
#define IR_EMITER 3
#define FIVE_SECONDS    5000

// IRsend Object and Remote Control object
IRsend irsend;
MideaIR remote_control(&irsend);

void setup(){
  // Define IR PIN as Output
  pinMode(IR_EMITER, OUTPUT);

  // Try to turn ON the Air Conditioner
  Serial.println(F("Trying to Turn ON the Air Conditioner..."));
  remote_control.turnON();
   delay(FIVE_SECONDS);

  // Try to turn OFF
  Serial.println(F("Trying to Turn OFF the Air Conditioner..."));
  remote_control.turnOFF();
  delay(FIVE_SECONDS);
  
  // Change mode
  remote_control.setState(true);

  // Change mode
  remote_control.setMode(mode_auto);
  remote_control.emit();
  delay(FIVE_SECONDS);
  
  // Change speed fan
  remote_control.setSpeedFan(fan_speed_1);
  remote_control.emit();
  delay(FIVE_SECONDS);
  
  // Change temperature to 22
  remote_control.setTemperature(22);
  remote_control.emit();
  delay(FIVE_SECONDS);
  
}

void loop(){}
