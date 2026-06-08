#include <cstdlib>
#include <ctime>
#include <cstdint>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cmath>
#include <fstream>
#include <SDL2/SDL.h>
#include "font.h"
#include "timers.h"
#include "keypad.h"

#define STACKSIZE 100
#define PC_START 0x200
#define WIDTH 64
#define HEIGHT 32
#define IPS 700

timer counter;
keypad pad;
int pressedKey;

uint8_t iCount; //to count number of instructions completed since last timer decrement
bool SHIFTFLAG;
bool JOFFSETFLAG = 0;

uint8_t RAM[4096];
uint8_t display[WIDTH][HEIGHT];

uint16_t PC;
uint16_t I;

uint16_t inst; //instructions are 16 bits this represents the entire instruction

uint8_t delay;
uint8_t sound;

uint8_t X; 	//second nibble
uint8_t	Y;	//third nibble
uint8_t N;	//fourth nibble
uint16_t NN;		//
uint16_t NNN;

uint8_t v0;
uint8_t v1;
uint8_t v2;
uint8_t v3;
uint8_t v4;
uint8_t v5;
uint8_t v6;
uint8_t v7;
uint8_t v8;
uint8_t v9;
uint8_t vA;
uint8_t vB;
uint8_t vC;
uint8_t vD;
uint8_t vE;
uint8_t vF;
uint8_t* registers[16] = {&v0,&v1,&v2,&v3,&v4,&v5,&v6,&v7,&v8,&v9,&vA,&vB,&vC,&vD,&vE,&vF};
struct stack{
	uint16_t* base;
	int size;
	stack(){
		base = new uint16_t[STACKSIZE];
		size = 0;
	}
	void push(uint16_t add){
		base[size] = add;
		size++;
	}
	void pop(){
		size--;
	}
	uint16_t top(){
		return(base[size-1]);
	}
	
};

stack theStack;

void printDisplay();
void fetch(){
	if(PC >=4096)
		PC = PC_START;
	inst = (RAM[PC]<< 8) & 0xFF00;
	inst= inst | ((RAM[PC+1]) & 0x00FF);

}
void decode(){
	uint8_t type = (inst >> 12);
	X = (inst & 0x0F00) >> 8;
	Y = (inst & 0x00F0) >> 4;
	N = (inst & 0x000F);
	NN =  (inst & 0x00FF);
	NNN =  (inst & 0x0FFF);
	switch(type){
		case 0x0:
			if(X == 0x0 && Y == 0xE && N == 0x0){
				//CLEAR SCREEN
				for(int i = 0; i<WIDTH; i++){
					memset(display[i],0,sizeof(display[i]));
				}
			}
			else if(X == 0x0 && Y == 0xE && N == 0xE){
				PC=theStack.top();
				theStack.pop();
			}
			break;
		case 0x1:
			//JUMP
			//DOESN'T increment PC after so set PC to NNN-2
			PC = NNN-2;
			break;
		case 0x2:
			theStack.push(PC);
			PC=NNN-2;
                        break;
		case 0x3:
			if(!(*registers[X] ^ NN)){
				PC += 2;
			}
                        break;
		case 0x4:
			if((*registers[X] ^ NN)){
                                PC += 2;
                        }

                        break;
		case 0x5:
			if(!(*registers[X] ^ *registers[Y])){
                                PC += 2;
                        }

                        break;
		case 0x6:
			std::cout<<"SET REGISTER X to NN "<<+X<<"  "<<+NN<<'\n';
			*registers[X] = NN;
                        break;
		case 0x7:
			std::cout<<"ADDED NN to REG X "<<+X<<"  "<<+NN<<'\n';
			*registers[X] += NN;
                        break;
		case 0x8:
			switch(N){
				case(0):
					*registers[X] = *registers[Y];
			        	break;
				case(1):
					*registers[X] = *registers[X] | *registers[Y];
                                        break;
				case(2):
					*registers[X] = *registers[X] & *registers[Y];
                                        break;
				case(3):
					*registers[X] = *registers[X] ^ *registers[Y];

                                        break;
	      			case(4):
					{
						uint8_t sum;
					
						sum  = *registers[X]+*registers[Y];
						if(sum < *registers[X] || sum < *registers[Y]){
							vF=1;
						}
						else
							vF=0;
						*registers[X]=sum;
					}
                                        break;
                                case(5):
					if(*registers[X] >= *registers[Y]){
						vF=1;
					}
					else{
						vF=0;
					}
					*registers[X] = *registers[X] - *registers[Y];
                                        break;
                                case(6):
					if(SHIFTFLAG){
						*registers[X] = *registers[Y];					
					}
					
					vF=(*registers[X]&0x01);
					*registers[X] = (*registers[X] >> 1);
					
                                        break;
                                case(7):
					if(*registers[Y] >= *registers[X]){
                                                vF=1;
                                        }
                                        else{
                                                vF=0;
                                        }
                                        *registers[X] = *registers[Y] - *registers[X];

                                        break;
                                case(0xE):
					 if(SHIFTFLAG){
                                                *registers[X] = *registers[Y];
                                        }

                                        vF=((*registers[X]&0x80)>>7);
                                        *registers[X] = ((*registers[X] << 1)& 0xFF);

                                        break;

			}
                        break;
		case 0x9:
			if((*registers[X] ^ *registers[Y])){
                                PC += 2;
                        }

                        break;
		case 0xA:
			I = NNN;
                        break;
		case 0xB:
			//JUMP WITH OFFSET
			{int reg = 0;
				if(JOFFSETFLAG){
					reg = +X;
				}
			PC = (NNN + *registers[reg] - 2);
			}
                        break;
		case 0xC:
			*registers[X] = (NN & (std::rand() % NN));
                        break;
		case 0xD:
			//DRAW
			{
				int x;
				int y = *registers[Y] % HEIGHT;
				vF = 0x00;
				uint8_t spriteData;
				int counter;
				for(int i = 0; i<N; i++){
					x = *registers[X] % WIDTH;
					counter = 7;
					spriteData = RAM[I+i];
//					std::cout<<"Sprite Data" <<+spriteData<<'\n';
					while(counter>=0){
						if(((spriteData >> counter)& 0x0001)){
							if(display[x][y]==1){
//								std::cout<<"TURNED OFF PIXEL at X: " << +x << "AND Y: " << y<<'\n'; 
								display[x][y]=0;
								vF=0x01;
							}
							else{
//								std::cout<<"TURNED ON PIXEL at X: " << x << "AND Y: " << y<<'\n';
								display[x][y]=1;
							}
						}
						x++;
//						std::cout<<"INC x\n";
						counter--;
						if(x>=WIDTH){
							break;
						}
							
					}
					y++;
					if(y>=HEIGHT){
						break;
					}
				}
			}
			printDisplay();
                        break;
		case 0xE:
			if(X>=0x0 && X<=0xF){
				bool cond = pad.valPressed(X);
				switch(NN){
					case 0x9E:	//skip if key pressed
						if(cond)
							PC += 2;
						break;
					case 0xA1:	//skip if key not pressed
						if(!cond)
							PC += 2;
						break;
				}
			}
                        break;
		case 0xF:
			switch(NN){
				case 0x07:
					*registers[X] = delay;
					break;
				case 0x15:
					delay = *registers[X];
					break;
				case 0x18:
					sound = *registers[X];
					break;
				case 0x1E:
					I = I + *registers[X];
					break;
				case 0x0A:
					//block until key is pressed
					if(pressedKey != -1){
						*registers[X] = pressedKey;			
					}
					else {
						PC -= 2;
					}
					break;
			}
                        break;

	
	}
	PC += 2;
}
void printDisplay(){
	char block = 219;
	for(int i = 0; i<HEIGHT; i++){
		for(int j=0; j<WIDTH; j++){
			if(+display[j][i]==1){
				std::cout<< "@" ;	
			}
			else{
				std::cout<<" ";
			}
			//std::cout << +display[j][i]<<" ";
		}
		std::cout<<" NEW LINE "<<'\n';
	}
	std::cout<<'\n';
};
void loadProgram(){
	std::ifstream program;
	program.open("ibm.ch8");
	int input;
	int start = PC;
	while(program){
		input = program.get();
		std::cout<<std::hex<<input<<" ";
		RAM[start]=static_cast<uint8_t>(input);
		start++;
	}
	std::cout << "\n";
}
int main(){
	stack test;
	iCount = 0;	
	test.push(0b00000010);
	test.push(0b00000001);
	PC = PC_START;
	memset(RAM, 0, sizeof(RAM));
	while(test.size){
	std::cout << test.top()<<'\n';
	test.pop();
	RAM[0]=0x00;
	RAM[1]=0xE0;
	RAM[2]=0b01010110;
	RAM[3]=0b01111000;
	}
	loadProgram();
	printDisplay();
	counter.init();
	counter.setIPS(IPS);
	pad.init();
	for(int i=0; 1==1;i++){
		counter.start();
		pressedKey = pad.pollKeys();
		if(iCount == std::ceil((0.f+IPS)/60.f)){
			iCount = 0;
			//	std::cout << "1 60th of a second!\n";
                        if(delay){
                                delay--;
                        }
			if(sound){
				sound--;
			}
                }
		fetch();
		decode();
		iCount++;
		counter.endAndWait();
		
	//std::cout<< "X: " << std::hex <<+X << " Y: " << +Y << " N: " << +N << " NN: " << NN << " NNN: " << NNN << "\n";
	
	}
	pad.kill();
	counter.kill();
	return 0;
}
