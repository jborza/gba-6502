
#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <stdio.h>
#include <stdlib.h>
#include "emu_gba.h"
#include "color.h"

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160
#define SCREEN_OFFSET_LEFT (SCREEN_WIDTH - SCREEN_HEIGHT) / 2
#define PIXEL_SIZE 5

#define MEM_VRAM 0x06000000

#define vid_mem ((u16 *)MEM_VRAM)

inline void draw_point(int x, int y, int clr)
{
    vid_mem[y * SCREEN_WIDTH + x] = clr;
};

inline void draw_square(int x, int y, int size, int color)
{
    for (int yy = 0; yy < size; yy++)
        for (int xx = 0; xx < size; xx++)
            vid_mem[(y + yy) * SCREEN_WIDTH + x + xx] = color;
}

#define CLR_BLACK 0x0000
#define CLR_RED 0x001F
#define CLR_LIME 0x03E0
#define CLR_YELLOW 0x03FF
#define CLR_BLUE 0x7C00
#define CLR_MAG 0x7C1F
#define CLR_CYAN 0x7FE0
#define CLR_WHITE 0x7FFF

int frame = 0;

//---------------------------------------------------------------------------------
// storage space for palette data
//---------------------------------------------------------------------------------
u16 PaletteBuffer[256];

//---------------------------------------------------------------------------------
void VblankInterrupt()
//---------------------------------------------------------------------------------
{
    frame += 1;
    scanKeys();
}

void draw_memory()
{
    for (int y = 0; y < 32; y++)
    {
        for (int x = 0; x < 32; x++)
        {
            //160x160
            //5x5 px box
            draw_square(x*PIXEL_SIZE+SCREEN_OFFSET_LEFT, y*PIXEL_SIZE, PIXEL_SIZE, get_color(state.memory[0x200 + x + y * DISP_WIDTH]));
        }
    }
}

//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main(void)
{
    //---------------------------------------------------------------------------------

    // Set up the interrupt handlers
    irqInit();

    irqSet(IRQ_VBLANK, VblankInterrupt);

    // Enable Vblank Interrupt to allow VblankIntrWait
    irqEnable(IRQ_VBLANK);

    // Allow Interrupts
    REG_IME = 1;

    SetMode(MODE_3 | BG2_ON); // screen mode & background to display

    initialize_palette();

    initialize_state();
    load_bin();
    reset_pc();

    int x = 0;
    while (1)
    {
        for (int i = 0; i < 256; i++)
            emu_tick();
        draw_memory();
        VBlankIntrWait();
    }
}