# ChipEmu

A CHIP-8 interpreter written in C++ for Linux, using SDL2 for graphics, keyboard input, and timing.

CHIP-8 is an interpreted programming language from the mid-1970s, originally designed to make game development easier on 8-bit microcomputers like the COSMAC VIP. Programs are distributed as compact ROM files and run on a simple virtual machine — 4KB of memory, 16 general-purpose registers, a 64x32 monochrome display, and a 16-key hex keypad. You can read more about it on [Wikipedia](https://en.wikipedia.org/wiki/CHIP-8).

This project implements the fetch-decode-execute cycle for the full standard CHIP-8 instruction set, with an SDL2 window for display and input.

## Features

- Full standard CHIP-8 opcode coverage (`0x0` – `0xF`), including:
  - Display clear, jumps, subroutine call/return
  - Conditional skips (`3xkk`, `4xkk`, `5xy0`, `9xy0`)
  - Arithmetic and logic ops (add, sub, AND/OR/XOR, shifts)
  - Sprite drawing with collision detection (`Dxyn`)
  - Keypad input (`Ex9E` / `ExA1` / `Fx0A`)
  - Delay and sound timers
  - BCD conversion, font character lookup, and memory store/load (`Fx33`, `Fx29`, `Fx55`, `Fx65`)
- SDL2-based display window and keyboard input
- Configurable instructions-per-second clock for timing
- Bundled test/demo ROMs (IBM logo, Corax+ opcode test, and others)

## Requirements

- A Linux environment
- `g++`
- [SDL2](https://www.libsdl.org/) development libraries (e.g. `libsdl2-dev` on Debian/Ubuntu)

## Building

```bash
git clone https://github.com/areed123/ChipEmu.git
cd ChipEmu
make clean; make
```

This produces a `chipEmu` executable in the project directory.

## Usage

Run the executable from a terminal:

```bash
./chipEmu
```

You'll be prompted for the path to a CHIP-8 ROM (`.ch8` file). The repo includes a few to try, e.g.:

```
Provide The filepath to the rom you want to read
Or type 'q' to exit the emulator
ibm.ch8
```

An SDL2 window will open and begin running the ROM. Press **Escape** in the window to return to the terminal, where you can load another ROM by entering its path, or type `q` to quit.

## Controls

The original CHIP-8 keypad is mapped to the keyboard as follows:

| CHIP-8 Keypad | Keyboard |
|:---:|:---:|
| 1 2 3 C | 1 2 3 4 |
| 4 5 6 D | q w e r |
| 7 8 9 E | a s d f |
| A 0 B F | z x c v |

## Project Structure

| File | Description |
|---|---|
| `chip.cpp` | Core interpreter: fetch/decode/execute loop, registers, memory, display, and SDL2 rendering |
| `keypad.h` / `keypad.cpp` | Keyboard-to-keypad input handling |
| `timers.h` / `timers.cpp` | Instructions-per-second clock used to pace emulation and drive the 60Hz delay/sound timers |
| `font.h` | Built-in hexadecimal font sprite data |
| `Makefile` | Build rules |
| `*.ch8` | Sample/test ROMs (IBM logo, Corax+ opcode test, etc.) |
| `TODO.txt` | Planned work and known issues |

## Roadmap

See [`TODO.txt`](./TODO.txt) for planned improvements. Sound output and broader cross-platform support are areas the interpreter doesn't currently cover.

## Acknowledgments

- [Wikipedia: CHIP-8](https://en.wikipedia.org/wiki/CHIP-8)
- The CHIP-8 community's test ROMs (e.g. Corax+ opcode test), used here to validate instruction behavior
