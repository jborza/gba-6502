#include "state.h"

#define MEMORY_SIZE 0xFFFF
#define PRG_START 0x0600

#define DISP_WIDTH 32
#define DISP_HEIGHT 32

extern State6502 state;
extern int last_key;
extern int frameskip;

extern int paused;
extern int show_diagnostics;
extern int show_memory;

void initialize_state();
void load_bin();
void emu_tick();
void reset_pc();
void reset_emulation();