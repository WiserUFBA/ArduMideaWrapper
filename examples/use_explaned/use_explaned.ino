#include <IRremote.h>
#include <MideaIR.h>
#define IR_EMITER 3

// IRsend Object and Remote Control object
IRsend irsend;
MideaIR remote_control(&irsend);

void setup(){
  // Define IR PIN as Output
  pinMode(IR_EMITER, OUTPUT);

  // Do Unit tests
}

void loop(){}
