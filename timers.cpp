#include "timers.h"
#include <iostream>

bool delayTimer::init(){
	if(!SDL_Init(SDL_INIT_TIMER)){
		reg = 0;
		start = SDL_GetPerformanceCounter();
		begin = SDL_GetPerformanceCounter();
		return true;
	}	
	return false;
}
bool delayTimer::kill(){
	SDL_QuitSubSystem(SDL_INIT_TIMER);
	return true;
}
bool delayTimer::setTimer(uint8_t time){
	reg = time;
	return true;
}
uint8_t delayTimer::getRegVal(){
	return reg;
}
void delayTimer::decrement(){
	begin = SDL_GetPerformanceCounter();
	if(reg){
                reg--;
        }
	end = SDL_GetPerformanceCounter();
	float elapsed = (end - begin)/ (float)SDL_GetPerformanceFrequency() * 1000.0f;
	//std::cout << elapsed << " milliseconds \n";
	SDL_Delay(1.6666f - elapsed);

	
}
bool timer::init(){
	if(!SDL_Init(SDL_INIT_TIMER)){
                return true;
        }
        return false;
}
bool timer::kill(){
        SDL_QuitSubSystem(SDL_INIT_TIMER);
        return true;
}
void timer::start(){
	step = SDL_GetPerformanceCounter();
}
void timer::endAndWait(){
	end=SDL_GetPerformanceCounter();
	float elapsed = (end - step)/ (float)SDL_GetPerformanceFrequency() * 1000.0f;
	SDL_Delay(1.6666f - elapsed);
	//SDL_Delay(100.6666f - elapsed);

}
