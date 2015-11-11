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

/*
    YOU CAN'T Change FAN SPEED on -MODE_AUTO and -MODE_NO_HUMIDITY  
    YOU CAN'T Change TEMPERATURE on -VENTILATE MODE
    YOU CAN'T Set    TURBO MODE on -VENTILATE MODE
*/

// Uncomment the following line to use old values for mode and fan speed
// #define OLD_MIDEA

// Comment the following line if you use the old values for mode and fan speed
#define NEW_MIDEA

// Enable heat mode on your fan
//#define MIDEA_COOL_HEAT 

#ifdef OLD_MIDEA
// Air Conditioner Modes
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
};
#endif

#ifdef NEW_MIDEA
enum Modes{
    mode_cool        = 0x0,
    mode_auto        = 0x8,
    mode_heat        = 0xC,
    mode_no_humidity = 0x4
};

enum FanSpeed{
    fan_auto    = 0xB,
    fan_speed_1 = 0x9,
    fan_speed_2 = 0x5,
    fan_speed_3 = 0x3
};
#endif

// Air Conditioner Fan Speeds

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

// Bytes to set ventilate Mode
#define VENTILATE_BYTE1     0xBF
#define VENTILATE_BYTE2     0xE4

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
    volatile uint8_t command_byte1;
    volatile uint8_t command_byte2;

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
    void    doVentilate();

    // Emmit the command
    void    emit();
};

#endif
