#include <IRremote.h>
#include <MideaIR.h>

#define IR_EMITER       3
#define FIVE_SECONDS    5000

// IRsend Object and Remote Control object
IRsend irsend;
MideaIR remote_control(&irsend);

void setup(){
    // Start communication in 9600
    Serial.begin(9600);
    Serial.println("Midea IR Unit Tests");
    Serial.println("Developed by: Jeferson Lima");
    Serial.println();
    Serial.println("Starting Unit Tests...");

    // Temp Variables
    int i;

    // Define IR PIN as Output
    pinMode(IR_EMITER, OUTPUT);

    // Do Unit tests
    // Try to turn ON the Air Conditioner
    Serial.println("Trying to Turn ON the Air Conditioner...");
    remote_control.turnON();
    delay(FIVE_SECONDS);

    // Try to turn OFF
    Serial.println("Trying to Turn OFF the Air Conditioner...");
    remote_control.turnOFF();
    delay(FIVE_SECONDS);

    // Change mode
    remote_control.setMode(mode_cool);

    // Retrieve mode
    if(remote_control.getMode() == mode_cool)
        Serial.println("Mode Cool - change OK");
    else
        Serial.println("Mode Cool - change FAIL");

    // Try to set this mode on the Air conditioner
    Serial.println("Trying to set the mode cool...");
    remote_control.emit();
    delay(FIVE_SECONDS);

    // Change mode
    remote_control.setMode(mode_heat);

    // Retrieve mode
    if(remote_control.getMode() == mode_heat)
        Serial.println("Mode Heat - change OK");
    else
        Serial.println("Mode Heat - change FAIL");

    // Try to set this mode on the Air conditioner
    Serial.println("Trying to set the mode heat...");
    remote_control.emit();
    delay(FIVE_SECONDS);

    // Change mode
    remote_control.setMode(mode_no_humidity);

    // Retrieve mode
    if(remote_control.getMode() == mode_no_humidity)
        Serial.println("Mode Humidity Remover - change OK");
    else
        Serial.println("Mode Humidity Remover - change FAIL");

    // Try to set this mode on the Air conditioner
    Serial.println("Trying to set the mode humidity remover...");
    remote_control.emit();
    delay(FIVE_SECONDS);

    // Change mode
    remote_control.setMode(mode_auto);

    // Retrieve mode
    if(remote_control.getMode() == mode_auto)
        Serial.println("Mode Auto - change OK");
    else
        Serial.println("Mode Auto - change FAIL");

    // Try to set this mode on the Air conditioner
    Serial.println("Trying to set the mode auto...");
    remote_control.emit();
    delay(FIVE_SECONDS);

    // Change speed fan
    remote_control.setSpeedFan(fan_off);

    // Retrieve mode
    if(remote_control.getSpeedFan() == fan_off)
        Serial.println("Fan Off - change OK");
    else
        Serial.println("Fan Off - change FAIL");

    // Try to set this mode on the Air conditioner
    Serial.println("Trying to set the turn off Fan...");
    remote_control.emit();
    delay(FIVE_SECONDS);

    // Change speed fan
    remote_control.setSpeedFan(fan_speed_1);

    // Retrieve mode
    if(remote_control.getSpeedFan() == fan_speed_1)
        Serial.println("Fan Speed 1 - change OK");
    else
        Serial.println("Fan Speed 1 - change FAIL");

    // Try to set this mode on the Air conditioner
    Serial.println("Trying to set the speed 1...");
    remote_control.emit();
    delay(FIVE_SECONDS);

    // Change speed fan
    remote_control.setSpeedFan(fan_speed_2);

    // Retrieve mode
    if(remote_control.getSpeedFan() == fan_speed_2)
        Serial.println("Fan Speed 2 - change OK");
    else
        Serial.println("Fan Speed 2 - change FAIL");

    // Try to set this mode on the Air conditioner
    Serial.println("Trying to set the speed 2...");
    remote_control.emit();
    delay(FIVE_SECONDS);

    // Change speed fan
    remote_control.setSpeedFan(fan_speed_3);

    // Retrieve mode
    if(remote_control.getSpeedFan() == fan_speed_3)
        Serial.println("Fan Speed 3 - change OK");
    else
        Serial.println("Fan Speed 3 - change FAIL");

    // Try to set this mode on the Air conditioner
    Serial.println("Trying to set the speed 3...");
    remote_control.emit();
    delay(FIVE_SECONDS);

    // Change speed fan
    remote_control.setSpeedFan(fan_auto);

    // Retrieve mode
    if(remote_control.getSpeedFan() == fan_auto)
        Serial.println("Fan Speed auto - change OK");
    else
        Serial.println("Fan Speed auto - change FAIL");

    // Try to set this mode on the Air conditioner
    Serial.println("Trying to set the speed auto...");
    remote_control.emit();
    delay(FIVE_SECONDS);

    // Change speed fan
    remote_control.setState(false);

    // Retrieve mode
    if(remote_control.getSpeedFan() == false)
        Serial.println("Set state false - 'turn off' - change OK");
    else
        Serial.println("Set state false - 'turn off' - change FAIL");

    // Try to set this mode on the Air conditioner
    Serial.println("Trying to set state false (turn off)...");
    remote_control.emit();
    delay(FIVE_SECONDS);

    // Change speed fan
    remote_control.setState(true);

    // Retrieve mode
    if(remote_control.getSpeedFan() == true)
        Serial.println("Set state true - 'turn on' - change OK");
    else
        Serial.println("Set state true - 'turn on' - change FAIL");

    // Try to set this mode on the Air conditioner
    Serial.println("Trying to set state true (turn on)...");
    remote_control.emit();
    delay(FIVE_SECONDS);

    // Change temperatures
    Serial.println("Starting temperature tests...");
    for(i = 17; i < 31; i++){
        Serial.print("Trying to set the temperature in ");
        Serial.println(i);

        remote_control.setTemperature(i);
        remote_control.emit();
        delay(FIVE_SECONDS);
    }

    Serial.println("Finishing tests...");
    Serial.println("Turning off the Air Conditioner...");

    remote_control.turnOFF();
    Serial.println("Finished all unit tests...");
}

void loop(){}
