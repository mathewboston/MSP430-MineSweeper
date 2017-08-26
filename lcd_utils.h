#ifndef lcd_utils_included

#include "booster1202.h"
#include "lcd_backend.h"

/* compute major & minor row numbers */
u_char lcd_getYMajor(u_char y);
u_char lcd_getYMinor(u_char y);

/* displays a chunk (byte of binary pixels) at the given address */
void lcd_setAddr(u_char x, u_char yMajor); /* set addr of next write  */
void lcd_writeChunk(char chunk); /* write chunk and increment x */

/* set addr & write */
void lcd_writeChunkAddr(char chunk, u_char xPos, u_char yMajor); 

/* converts ints to character sequences */
char* itoa(int value, char* result, int base);

#define lcd_utils_included
#endif // lcd_utils_included
