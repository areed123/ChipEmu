#include <map>
#include <iostream>
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
	if(!SDL_Init(SDL_INIT_VIDEO)){

		return true;
	}	
	return false;
}
bool keypad::kill(){
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	return(true);
}
bool keypad::valPressed(uint8_t key){
	//char* keys = SDL_GetKeyboardState(NULL);
	return(SDL_GetKeyboardState(NULL)[map[key]]);	
}
int keypad::pollKeys(){
	SDL_Event event;
	bool flag = false;
	int val = -1;
	while(SDL_PollEvent(&event) != 0 ){
		std::cout << "Polling Keys \n";
		if(!flag){
			if(event.type == SDL_KEYDOWN){
				if(event.key.keysym.sym == SDLK_ESCAPE){
					std::cout << "ESCAPE PRESSED\n";
					return -2;//exit code for the emulator
				}
				flag = true;
				switch(event.key.keysym.sym){
					case SDLK_1:
						val = 0x1;
						break;
					case SDLK_2:
						val = 0x2;
						break;
					case SDLK_3:
						val = 0x3;
						break;
					case SDLK_4:
						val = 0xC;
						break;
					case SDLK_q:
						val = 0x4;
						break;
					case SDLK_w:
						val = 0x5;
						break;
					case SDLK_e:
						val = 0x6;
						break;
					case SDLK_r:
						val = 0xD;
						break;
					case SDLK_a:
						val = 0x7;
						break;
					case SDLK_s:
						val = 0x8;
						break;
					case SDLK_d:
						val = 0x9;
						break;
					case SDLK_f:
						val = 0xE;
						break;
					case SDLK_z:
						val = 0xA;
						break;
					case SDLK_x:
						val = 0x0;
						break;
					case SDLK_c:
						val = 0xB;
						break;
					case SDLK_v:
						val = 0xF;
						break;
					default:
						flag = false;
				}
			}
		}
	}
	return val;
}
