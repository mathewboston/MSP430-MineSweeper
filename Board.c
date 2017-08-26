#include "lcd_utils.h"
static const u_char chunkMasks[9] = {0x0, 0x1, 0x3, 0x7, 0xf, 0x1f, 0x3f, 0x7f, 0xff};

static void drawBoard(){
  
  lcd_writeChunkAddr(chunkMasks[6],50,50);
}
