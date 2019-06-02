#include "color.h"

int get_color(int byte){
    return palette[byte & 0x0f];
}

void initialize_palette(){
//     //RGBA
palette[0] = 0x0;
palette[1] = 0x7fff;
palette[2] = 0x11;
palette[3] = 0x77f5;
palette[4] = 0x6519;
palette[5] = 0x2b20;
palette[6] = 0x5400;
palette[7] = 0x3bbd;
palette[8] = 0x2a3b;
palette[9] = 0x10c;
palette[10] = 0x39df;
palette[11] = 0x18c6;
palette[12] = 0x39ce;
palette[13] = 0x33f5;
palette[14] = 0x7e20;
palette[15] = 0x5ef7;
}