#include "keypad.h"
int mapping[16] = {
	SDL_SCANCODE_1, SDL_SCANCODE_2, SDL_SCANCODE_3, SDL_SCANCODE_4,
	SDL_SCANCODE_Q, SDL_SCANCODE_W, SDL_SCANCODE_E, SDL_SCANCODE_R,
	SDL_SCANCODE_A, SDL_SCANCODE_S, SDL_SCANCODE_D, SDL_SCANCODE_F,
	SDL_SCANCODE_Z, SDL_SCANCODE_X, SDL_SCANCODE_C, SDL_SCANCODE_V
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
	return(SDL_GetKeyboardState(NULL)[mapping[key]]);	
}
