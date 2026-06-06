#ifndef KEYPAD_H
#define KEYPAD_H
#include <cstdint>
#include <SDL2/SDL.h>
class keypad{
	public:
		bool init();
		bool kill();
		bool valPressed(uint8_t key);
		int pressed(); //for checking if a key has been pressed since the previous instruction
};

#endif
