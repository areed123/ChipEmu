#include <map>
#include "keypad.h"

std::map<int, int> map = {
	{0x1, SDL_SCANCODE_1}, 
	{0x2, SDL_SCANCODE_2},
	{0x3, SDL_SCANCODE_3}, 
	{0xC, SDL_SCANCODE_4},
	{0x4, SDL_SCANCODE_Q}, 
	{0x5, SDL_SCANCODE_W},
	{0x6, SDL_SCANCODE_E},
	{0xD, SDL_SCANCODE_R},
	{0x7, SDL_SCANCODE_A},
	{0x8, SDL_SCANCODE_S},
	{0x9, SDL_SCANCODE_D},
	{0xE, SDL_SCANCODE_F},
	{0xA, SDL_SCANCODE_Z},
	{0x0, SDL_SCANCODE_X},
	{0xB, SDL_SCANCODE_C},
	{0xF, SDL_SCANCODE_V}
};
bool keypad::init(){
	if(!SDL_Init(SDL_INIT_EVENTS)){
		return true;
	}	
	return false;
}
bool keypad::kill(){
	SDL_QuitSubSystem(SDL_INIT_TIMER);
	return(true);
}
bool keypad::valPressed(uint8_t key){
	//char* keys = SDL_GetKeyboardState(NULL);
	return(SDL_GetKeyboardState(NULL)[map[key]]);	
}
