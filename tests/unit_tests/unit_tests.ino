#include <IRremote.h>
#include <MideaIR.h>

#define IR_EMITER       3
#define TWO_SECONDS     2000
#define FIVE_SECONDS    5000
#define TEN_SECONDS     10000

// IRsend Object and Remote Control object
IRsend irsend;
MideaIR remote_control(&irsend);

void setup(){
    // Start communication in 9600
    Serial.begin(9600);
    Serial.println(F("Midea IR Unit Tests"));
    Serial.println(F("Developed by: Jeferson Lima"));
    Serial.println();
    Serial.println(F("Starting Unit Tests..."));

    // Temp Variables
    int i;

    // Define IR PIN as Output
    pinMode(IR_EMITER, OUTPUT);

    // Do Unit tests
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

    remote_control.setMode(mode_auto);

    // Retrieve mode
    if(remote_control.getMode() == mode_auto)
        Serial.println(F("Mode Auto - change OK"));
    else
        Serial.println(F("Mode Auto - change FAIL"));

    // Try to set this mode on the Air conditioner
    Serial.println(F("Trying to set the mode auto..."));
    remote_control.emit();
    delay(FIVE_SECONDS);

    // Change mode
    #ifdef MIDEA_COOL_HEAT
    remote_control.setMode(mode_heat);

    // Retrieve mode
    if(remote_control.getMode() == mode_heat)
        Serial.println(F("Mode Heat - change OK"));
    else
        Serial.println(F("Mode Heat - change FAIL"));

    // Try to set this mode on the Air conditioner
    Serial.println(F("Trying to set the mode heat..."));
    remote_control.emit();
    delay(FIVE_SECONDS);
    #endif

    // Change mode
    remote_control.setMode(mode_no_humidity);

    // Retrieve mode
    if(remote_control.getMode() == mode_no_humidity)
        Serial.println(F("Mode Humidity Remover - change OK"));
    else
        Serial.println(F("Mode Humidity Remover - change FAIL"));

    // Try to set this mode on the Air conditioner
    Serial.println(F("Trying to set the mode humidity remover..."));
    remote_control.emit();
    delay(FIVE_SECONDS);

    // Change mode
    remote_control.setMode(mode_cool);

    // Retrieve mode
    if(remote_control.getMode() == mode_cool)
        Serial.println(F("Mode Cool - change OK"));
    else
        Serial.println(F("Mode Cool - change FAIL"));

    // Try to set this mode on the Air conditioner
    Serial.println(F("Trying to set the mode cool..."));
    remote_control.emit();
    delay(FIVE_SECONDS);

    // Change speed fan
    #ifdef OLD_MIDEA
    remote_control.setSpeedFan(fan_off);


    // Retrieve mode
    if(remote_control.getSpeedFan() == fan_off)
        Serial.println(F("Fan Off - change OK"));
    else
        Serial.println(F("Fan Off - change FAIL"));

    // Try to set this mode on the Air conditioner
    Serial.println(F("Trying to set the turn off Fan..."));
    remote_control.emit();
    delay(FIVE_SECONDS);
    #endif

    // Change speed fan
    remote_control.setSpeedFan(fan_speed_1);

    // Retrieve mode
    if(remote_control.getSpeedFan() == fan_speed_1)
        Serial.println(F("Fan Speed 1 - change OK"));
    else
        Serial.println(F("Fan Speed 1 - change FAIL"));

    // Try to set this mode on the Air conditioner
    Serial.println(F("Trying to set the speed 1..."));
    remote_control.emit();
    delay(FIVE_SECONDS);

    // Change speed fan
    remote_control.setSpeedFan(fan_speed_2);

    // Retrieve mode
    if(remote_control.getSpeedFan() == fan_speed_2)
        Serial.println(F("Fan Speed 2 - change OK"));
    else
        Serial.println(F("Fan Speed 2 - change FAIL"));

    // Try to set this mode on the Air conditioner
    Serial.println(F("Trying to set the speed 2..."));
    remote_control.emit();
    delay(FIVE_SECONDS);

    // Change speed fan
    remote_control.setSpeedFan(fan_speed_3);

    // Retrieve mode
    if(remote_control.getSpeedFan() == fan_speed_3)
        Serial.println(F("Fan Speed 3 - change OK"));
    else
        Serial.println(F("Fan Speed 3 - change FAIL"));

    // Try to set this mode on the Air conditioner
    Serial.println(F("Trying to set the speed 3..."));
    remote_control.emit();
    delay(FIVE_SECONDS);

    // Change speed fan
    remote_control.setSpeedFan(fan_auto);

    // Retrieve mode
    if(remote_control.getSpeedFan() == fan_auto)
        Serial.println(F("Fan Speed auto - change OK"));
    else
        Serial.println(F("Fan Speed auto - change FAIL"));

    // Try to set this mode on the Air conditioner
    Serial.println(F("Trying to set the speed auto..."));
    remote_control.emit();
    delay(FIVE_SECONDS);

    // Change state
    remote_control.setState(false);

    // Retrieve state
    if(remote_control.getState() == false)
        Serial.println(F("Set state false - 'turn off' - change OK"));
    else
        Serial.println(F("Set state false - 'turn off' - change FAIL"));

    // Try to set this state on the Air conditioner
    Serial.println(F("Trying to set state false (turn off)..."));
    remote_control.emit();
    delay(FIVE_SECONDS);

    // Change state
    remote_control.setState(true);

    // Retrieve mode
    if(remote_control.getState() == true)
        Serial.println(F("Set state true - 'turn on' - change OK"));
    else
        Serial.println(F("Set state true - 'turn on' - change FAIL"));

    // Try to set this state on the Air conditioner
    Serial.println(F("Trying to set state true (turn on)..."));
    remote_control.emit();
    delay(FIVE_SECONDS);

    // Change temperatures
    Serial.println(F("Starting temperature tests..."));
    for(i = 17; i < 31; i++){
        Serial.print(F("Trying to set the temperature in "));
        Serial.println(i);

        remote_control.setTemperature(i);
        remote_control.emit();
        delay(FIVE_SECONDS);
    }

    /* 
        Advanced and Complex features don't have states so to start the feature
        turn one time, to stop the feature turn it again
    */

    // Advanced Features
    // One time to start oscilate
    Serial.println(F("Testing advanced features..."));
    Serial.println(F("Testing oscilation..."));
    remote_control.doOscilate();
    delay(TEN_SECONDS);
    // And other time to stop oscilate
    remote_control.doOscilate();
    delay(TEN_SECONDS);
    // The same in the command to change direction, one time to stop if is oscilating
    // and the same command again to change direction
    Serial.println(F("Testing direction chage..."));
    remote_control.doChangeDirection();
    delay(TWO_SECONDS);
    remote_control.doChangeDirection();
    delay(TWO_SECONDS);
    remote_control.doChangeDirection();
    delay(TWO_SECONDS);
    remote_control.doChangeDirection();
    delay(TWO_SECONDS);
    // To finish this test put the air conditioner in the oscilate mode again
    remote_control.doOscilate();

    // Complex Features
    Serial.println(F("Testing complex features..."));
    Serial.println(F("Testing sound response..."));
    remote_control.setNoSound();
    delay(TWO_SECONDS);
    remote_control.setTemperature(20);
    remote_control.emit();
    delay(TWO_SECONDS);
    remote_control.setTemperature(22);
    remote_control.emit();
    delay(TWO_SECONDS);
    remote_control.setNoSound();
    delay(FIVE_SECONDS);
    Serial.println(F("Testing Turbo mode..."));
    remote_control.seTurboMode();
    delay(FIVE_SECONDS);
    remote_control.seTurboMode();
    delay(TWO_SECONDS);
    Serial.println(F("Testing Ionize mode..."));
    remote_control.setIonizeMode();
    delay(FIVE_SECONDS);
    remote_control.setIonizeMode();
    delay(TWO_SECONDS);
    Serial.println(F("Testing clean mode..."));
    remote_control.doCleanDevice();
    delay(FIVE_SECONDS);
    remote_control.doCleanDevice();
    delay(TWO_SECONDS);

    Serial.println(F("Finishing tests..."));
    Serial.println(F("Turning off the Air Conditioner..."));

    remote_control.turnOFF();
    Serial.println(F("Finished all unit tests..."));
}

void loop(){}
