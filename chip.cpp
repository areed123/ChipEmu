#include <cstdint>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include "font.h"

#define STACKSIZE 100
#define PC_START 0
uint8_t RAM[4096];
uint8_t display[8][4];

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
void fetch(){
	if(PC >=4096)
		PC = 0;
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
			break;
		case 0x1:
			break;
		case 0x2:
                        break;
		case 0x3:
                        break;
		case 0x4:
                        break;
		case 0x5:
                        break;
		case 0x6:
                        break;
		case 0x7:
                        break;
		case 0x8:
                        break;
		case 0x9:
                        break;
		case 0xA:
                        break;
		case 0xB:
                        break;
		case 0xC:
                        break;
		case 0xD:
                        break;
		case 0xE:
                        break;
		case 0xF:
                        break;

	
	}
	PC += 2;
}
int main(){
	stack test;
	test.push(0b00000010);
	test.push(0b00000001);
	PC = PC_START;
	memset(RAM, 0, sizeof(RAM));
	while(test.size){
	std::cout << test.top()<<'\n';
	test.pop();
	RAM[0]=0b00010010;
	RAM[1]=0b00110100;
	RAM[2]=0b01010110;
	RAM[3]=0b01111000;
	}
	for(int i=0; i<2;i++){
		fetch();
		decode();
	std::cout<< "X: " << +X << " Y: " << +Y << " N: " << +N << " NN: " << NN << " NNN: " << NNN << "\n";
	
	}
	return 0;
}
