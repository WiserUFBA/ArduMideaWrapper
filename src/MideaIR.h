/* 
    Author:     Jeferson Lima
    Date:       2015-11-05
    License:    GNU GPL

    *** Developed at WiserUFBA Research Group *** 
                        ***
*/
#ifndef MideaIR_h
#define MideaIR_h

#include <stdint.h>
#include <IRremote.h>


/*  fan_speed   = 1110: off     1011: auto;   1001: 1,      0101: 2,      0011: 3
    command     = 0000: cool,   1000: auto,   1100: heat,   1101: humidity extraction */
enum Modes{
    mode_cool        = 0x0,
    mode_auto        = 0x8,
    mode_heat        = 0xC,
    mode_no_humidity = 0xD
};

enum FanSpeed{
    fan_off     = 0xE,
    fan_auto    = 0xB,
    fan_speed_1 = 0x9,
    fan_speed_2 = 0x5,
    fan_speed_3 = 0x3
}

// Midea IR Times
#define MIDEA_MARK_LIMIT    4200
#define MIDEA_MARK_LIMIT2   550
#define MIDEA_SPACE_LIMIT   4500
#define MIDEA_MARK          450
#define MIDEA_SPACE         1700
#define MIDEA_SPACE2        600

// Midea IR Frequency
#define MIDEA_FREQUENCY     38

// Midea IR Codes
#define MIDEA_START_BYTE    0xB2

// Bytes to turn off Midea Air Conditioner
#define STOP_MIDEA_BYTE1    0x7B
#define STOP_MIDEA_BYTE2    0xE0

class MideaIR{
private:
    /* Basic Functions */
    uint8_t mode;
    uint8_t temperature;
    uint8_t speed_fan;
    bool    state;
    /* Complex Feature */
    bool    osci_dir;
    /* Extra Functions */
    bool    sleep;
    bool    turbo;
    bool    sound;
    /* IR Emitter Object */
    IRsend  *irsend;

    /* Control Bytes */
    uint8_t command_byte1;
    uint8_t command_byte2;

    /* Low Level Operations */
    void    loWLevelEmit();
    void    generateCommand();
    void    emitByte(uint8_t);
public:
    // Construct
    MideaIR(IRsend *);

    /* Basic Functions */
    void    turnON();
    void    turnOFF();

    /* Class Based Functions */
    // Change Values
    void    setMode(uint8_t);
    void    setState(bool);
    void    setSpeedFan(int);
    void    setTemperature(int);
    // Retrieve Values
    uint8_t getMode();
    bool    getState();
    uint8_t getSpeedFan();
    uint8_t getTemperature();

    /* Complex Buttons */
    void    doOscilate();
    void    doChangeDirection();

    // Emmit the command
    void    emit();
};

#endif