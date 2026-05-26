#include <cstdint>
#include <iostream>
#include "font.h"

#define STACKSIZE 100
uint8_t RAM[4096];
uint8_t display[8][4];

uint16_t PC;
uint16_t I;

uint8_t delay;
uint8_t sound;

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
int main(){
	stack test;
	test.push(0b00000010);
	
	test.push(0b00000001);
	while(test.size){
	std::cout << test.top()<<'\n';
	test.pop();
	}
	return 0;
}
