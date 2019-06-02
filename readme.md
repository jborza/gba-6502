# gba-6502

MOS 6502 emulator for GBA. Runs the same binaries as 6502asm.com fantasy console.
The screen is 32x32 pixels starting from address $200, using a 16-color palette.

## how to run your own binaries
1. Compile binaries with [6502js](https://jborza.github.io/6502js/) - develop, assemble, click `binary`.
2. Convert binary into a C hex array with `gen/gen_bin_c.py`
3. Paste hex array into `load_bin_from_memory` in `emu_gba.c`
4. Adjust the size of the binary in `load_bin_from_memory` (see the memcpy call)


## build instructions
Run `make` with [devkitPro](https://devkitpro.org/) installed.
