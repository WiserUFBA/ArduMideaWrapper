/* 
    Author:     Jeferson Lima
    Date:       2015-11-05
    License:    GNU GPL

    *** Developed at WiserUFBA Research Group *** 
                        ***
*/
#include "MideaIR.h"
#include <stdint.h>
#include <IRremote.h>

MideaIR::MideaIR(IRsend *ref){
    /* Initialize the variables with the default values */
    // Set the temperature on 20 and state in false (off)
    temperature   = 20;
    state         = false;
    
    // Initialize Speed and Mode in auto
    mode          = mode_auto;
    speed_fan     = fan_auto;
    
    // Disable Complex Features
    sleep         = false;

    // Zero the command bytes
    command_byte1 = 0;
    command_byte2 = 0;

    // IR Emiter Reference
    irsend = ref;
}

/* Class Based Functions */
// Change Values
void MideaIR::setState(bool new_state){
    state = new_state;
}

void MideaIR::setMode(uint8_t new_mode){
    switch(new_mode){
        case mode_ventilate  :
        case mode_cool       :
        case mode_auto       :
        #ifdef MIDEA_COOL_HEAT
        case mode_heat       :
        #endif
        case mode_no_humidity:
            mode = new_mode; break;
        default:
            mode = mode_auto;
    }
}

void MideaIR::setSpeedFan(int new_speed_fan){
    switch(new_speed_fan){
        #ifdef OLD_MIDEA
        case fan_off    :
        #endif
        case fan_auto   :
        case fan_speed_1:
        case fan_speed_2:
        case fan_speed_3:
            speed_fan = new_speed_fan; break;
        default: 
            speed_fan = fan_auto;
    }
}

void MideaIR::setTemperature(int new_temperature){
    if(new_temperature > 30)
        temperature = 30;
    else if(new_temperature < 17)
        temperature = 17;
    else
        temperature = new_temperature;
}

// Retrieve Valuestemperature
uint8_t MideaIR::getMode(){
    return mode;
}

bool MideaIR::getState(){
    return state;
}

uint8_t MideaIR::getSpeedFan(){
    return speed_fan;
}

uint8_t MideaIR::getTemperature(){
    return temperature;
}

// Generate command bytes
void MideaIR::generateCommand(){
    /*  The Midea Air Conditioner is controlled by two bytes that defines
        all comands in the controller. Basically what we have is the following
        mask: [1011 0010] [ffff 1111] [ttttcccc]
        As pointed by Daniel Veillard in the post http://veillard.com/embedded/midea.html
        Daniel said that we don't understand some values like temperature, for this we 
        had expanded his research. First he have understand how temperature is definied,
        and is basically 17 - temperature you want and then convert this to grey code,
        really strange for a programmer, but make sense at embedded technologies, another
        thing that we discovered is how perfom some "complex features" like, night mode,
        turbo mode, ionize mode, sleep mode (I think they are different in something that
        I don't care) and other functions that sucks '-_-.
        The mask that we use here is the following:
         START BYTE   FIRST BYTE   LAST BYTE
        [1011  0010] [ssss  ffff] [tttt mmmm]
        - ssss = Fan Speed
        - ffff = Features
        - tttt = Temperature
        - mmmm = Mode
    */

    uint8_t b_mode;
    uint8_t b_feature;
    uint8_t b_temperature;
    uint8_t b_fan_speed;
    uint8_t aux;

    // If the logic state of the Air Conditioner is off, turn off
    if(!state){
        command_byte1 = STOP_MIDEA_BYTE1;
        command_byte2 = STOP_MIDEA_BYTE2;
        return;
    }

    // Prepare Temperature
    /* I Can't see the logic in 27 and 28 temperatures */
    if(temperature == 27)
        b_temperature = 9;
    else if(temperature == 28)
        b_temperature = 8;
    else{
        aux = temperature - 17;
        aux = (aux >> 1) ^ aux; // -> Convert decimal into grey code
        b_temperature = aux;
    }

    // Prepare Mode and Fan Speed are alreay prepared so just copy the values to the temp var
    b_mode      = mode; 
    b_fan_speed = ((mode == mode_auto) || (mode == mode_no_humidity)) ? ESPECIAL_SPEED_FAN : speed_fan;

    // Prepare Features
    b_feature = 0xF; // <- Not implemented yet

    // Assembly First Byte
    command_byte1 = (b_fan_speed << 4)   | (b_feature);

    // Assembly Last Byte
    if(mode == mode_ventilate)
        command_byte2 = VENTILATE_BYTE2;
    else
        command_byte2 = (b_temperature << 4) | (b_mode);
}

void MideaIR::emitByte(uint8_t byte_to_send){
    // Thanks to Daniel Veillard, for this incredible function :D
    // And thanks to Tom to help us with this work
    // Tom Topic about Midea : 
    // http://thebloughs.net/design-a-custom-ac-timer/
    int i;

    // Pick the current byte, and his mask
    uint8_t cur = byte_to_send;
    uint8_t mask = 0x80;

    // Emit the first Byte
    for (i = 0;i < 8;i++) {
        irsend->mark(MIDEA_MARK);
        if (cur & mask)
            irsend->space(MIDEA_SPACE);
        else
            irsend->space(MIDEA_SPACE2);
        mask >>= 1;
    }

    // Neg bitwise this byte with his mask
    cur = ~byte_to_send;
    mask = 0x80;

    // And emit the same byte negate
    for (i = 0;i < 8;i++) {
        irsend->mark(MIDEA_MARK);
        if (cur & mask)
            irsend->space(MIDEA_SPACE);
        else
            irsend->space(MIDEA_SPACE2);
        mask >>= 1;
    }
}

void MideaIR::loWLevelEmit(){
    // Start Communication
    irsend->mark(MIDEA_MARK_LIMIT);
    irsend->space(MIDEA_SPACE_LIMIT);
    
    // Emit Some bytes
    emitByte(MIDEA_START_BYTE);
    emitByte(command_byte1);
    emitByte(command_byte2);

    // End Communication
    irsend->mark(MIDEA_MARK_LIMIT2);
    irsend->space(MIDEA_SPACE_LIMIT);
}

// Emit the command
void MideaIR::emit(){
    // Prepare the command bytes
    generateCommand();

    // Set IR Configuration
    irsend->enableIROut(MIDEA_FREQUENCY);

    // Send two times the same command, we have not discovered why this is necessary :?
    loWLevelEmit();
    loWLevelEmit();
}

/* Basic Functions */
void MideaIR::turnON(){
    state = true;
    emit();
}

void MideaIR::turnOFF(){
    state = false;
    emit();
}

/* Advanced Buttons */

void MideaIR::doOscilate(){
    // Configure some bytes 
    command_byte1 = OSCILATE_BYTE1;
    command_byte2 = ADVANCED_BYTE2;
   
    // Set IR Configuration
    irsend->enableIROut(MIDEA_FREQUENCY);

    // Send two times the same command, we have not discovered why this is necessary :?
    loWLevelEmit();
    loWLevelEmit();
}

void MideaIR::doChangeDirection(){
    // Configure some bytes 
    command_byte1 = DIRECTION_BYTE1;
    command_byte2 = ADVANCED_BYTE2;
    
     // Set IR Configuration
    irsend->enableIROut(MIDEA_FREQUENCY);

    // Send two times the same command, we have not discovered why this is necessary :?
    loWLevelEmit();
    loWLevelEmit();
}

/* Complex Buttons */
void MideaIR::lowLevelComplexEmit(){
    // Start Communication
    irsend->mark(MIDEA_MARK_LIMIT);
    irsend->space(MIDEA_SPACE_LIMIT);
    
    // Emit Some bytes
    emitByte(MIDEA_COMPLEX_BYTE1);
    emitByte(MIDEA_COMPLEX_BYTE2);
    emitByte(command_byte2);

    // End Communication
    irsend->mark(MIDEA_MARK_LIMIT2);
    irsend->space(MIDEA_SPACE_LIMIT);
}

void MideaIR::complexEmit(){
    // Set IR Configuration
    irsend->enableIROut(MIDEA_FREQUENCY);

    // Send two times the same command, we have not discovered why this is necessary :?
    lowLevelComplexEmit();
    lowLevelComplexEmit();
}

void MideaIR::doCleanDevice(){
    // Change the value of the command_byte2 and then emit the code
    command_byte2 = CLEAN_DEVICE;
    complexEmit();
}
// ~ Not Working Properly
void MideaIR::setNoSound(){
    // Change the value of the command_byte2 and then emit the code
    command_byte2 = NO_SOUND_MODE;
    complexEmit();
}

void MideaIR::seTurboMode(){
    // Change the value of the command_byte2 and then emit the code
    command_byte2 = TURBO_MODE;
    complexEmit();
}

void MideaIR::setIonizeMode(){
    // Change the value of the command_byte2 and then emit the code
    command_byte2 = IONIZE_MODE;
    complexEmit();
}
