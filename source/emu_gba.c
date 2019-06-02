#include "emu_gba.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "disassembler.h"
#include "cpu.h"

State6502 state;
int last_key;

int paused = 1;
int show_diagnostics = 1;
int show_memory = 0;

int frameskip = 128;

void initialize_state(){
	clear_state(&state);
	state.memory = malloc(MEMORY_SIZE);
	memset(state.memory, 0, MEMORY_SIZE);
}

void load_bin_from_memory(){
    char bin[] = {0xa9,0x2,0x85,0x1,0xa9,0x3,0x85,0x3,0xa9,0x4,0x85,0x5,0xa9,0x5,0x85,0x7,0xa9,0x33,0x85,0x10,0xa9,0xaa,0x85,0x11,0xa4,0xfe,0xa5,0xfe,0x91,0x0,0x4a,0x4a,0x4a,0x4a,0x4a,0x4a,0x4a,0x91,0x2,0x5,0x11,0x91,0x4,0xa6,0xfe,0x86,0x20,0x5,0x20,0x91,0x6,0x4c,0x18,0x6};
    memcpy(state.memory + PRG_START, bin, 54);
}

byte * read_bin(const char *filename, int* bin_file_size) {
	FILE* file = fopen(filename, "rb");
	if (!file) {
		exit(1);
	}
	fseek(file, 0, SEEK_END);
	*bin_file_size = ftell(file);

	rewind(file);

	byte* buffer = malloc(*bin_file_size);
	size_t read = fread(buffer, sizeof(byte), *bin_file_size, file);
	fclose(file);
	return buffer;
}

void load_bin(){
    // int bin_file_size = 0;
    // byte *bin = read_bin("bins/random.bin", &bin_file_size);
   	// memcpy(state.memory + PRG_START, bin, bin_file_size);
    load_bin_from_memory();
}

void reset_pc(){
    state.pc = PRG_START;
}

void reset_emulation(){
    initialize_state();
    load_bin();
    reset_pc();
}

void emu_tick(){
    state.memory[0xFF] = last_key & 0xFF;
    //generate random
	state.memory[0xfe] = rand() & 0xFF;
    if(state.flags.b != 1)
	    emulate_6502_op(&state);
}