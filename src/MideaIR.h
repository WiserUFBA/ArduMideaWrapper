/* 
	Author: 	Jeferson Lima
	Date: 		2015-11-05
	License: 	GNU GPL

	*** Developed at WiserUFBA Research Group *** 
						***
*/
#ifndef MideaIR_h
#define MideaIR_h

#include <stdint.h>
#include <IRremote.h>

class MideaIR{
private:
	/* Basic Functions */
    uint8_t mode;
    uint8_t temperature;
    uint8_t speed_fan;
	bool 	state;
    /* Complex Feature */
    bool 	osci_dir;
    /* Extra Functions */
    bool	sleep;
    bool 	turbo;
    bool 	sound;
    /* IR Emitter Object */
    IRsend 	*irsend;

    /* Control Bytes */
    uint8_t command_byte1;
    uint8_t command_byte2;
    uint8_t command_byte3;
    uint8_t command_byte4;
public:
	// Construct
	MideaIR(IRsend);

	/* Basic Functions */
	// Change Values
	void 	setMode(char);
	void 	setState(bool);
	void 	setSpeedFan(int);
	void 	setTemperature(int);
	// Retrieve Values
	char 	getMode();
	uint8_t	getState();
	uint8_t getSpeedFan();
	uint8_t getTemperature();

	// Emit the code
	void 	emmit();
};

#endif