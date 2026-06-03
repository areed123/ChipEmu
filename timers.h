#ifndef TIMERS_H
#define TIMERS_H
#include <cstdint>
#include <SDL2/SDL.h>
class delayTimer{
		uint8_t reg;
		Uint64 ticks;
		Uint64 start;
		Uint64 end;
		Uint64 begin;
		float msPerInst;
	public:
		bool setIPS(int ips);
		bool init();
		bool kill();
		uint8_t getRegVal();
		bool setTimer(uint8_t time);
		void decrement();
};
class timer{
	Uint64 step;
	Uint64 end;
	float msPerInst;
	public:
       		bool init();
		bool setIPS(int ips);
		bool kill();
		void start();
		void endAndWait();
};
#endif
