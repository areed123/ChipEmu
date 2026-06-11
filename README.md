# Chip 8 emulator/intepreter Project
## Welcome!
This is my implementation of a Chip-8 interpreter. Chip-8 is an interpreted language that you can read more about [here](https://en.wikipedia.org/wiki/CHIP-8)

This project was written in C++ for Linux and uses/requires the SDL2 library to handle keyboard input and timing.

## Usage
To compile the emulator clone this repo and use the Makefile with "make clean; make" and run from terminal
Provide the file path to a CHIP-8 rom to stdin and a window will open to run the rom
Press Escape in the opened window to return to terminal and type 'q' to exit or provide a filepath to another ROM

The emulator uses the standard controls as most CHIP-8 emulators 
Qwerty Key to CHIP-8 Keypad
---------------------------
1 -> 1  
2 -> 2  
3 -> 3  
4 -> C  
q -> 4  
w -> 5  
e -> 6  
r -> D  
a -> 7  
s -> 8  
d -> 9  
f -> E  
z -> A  
x -> O  
c -> B  
v -> F  
