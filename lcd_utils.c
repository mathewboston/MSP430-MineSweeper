#include "lcd_utils.h"

/* computes the major row number for 
 * a given row number
 */
u_char lcd_getYMajor(u_char y)
{
    // rows are grouped as bytes
    // therefore the major row number
    // is row # divided by 8
    return (y >> 3);
}

/* computes the minor row number for 
 * a given row number
 */
u_char lcd_getYMinor(u_char y)
{
    // rows are grouped as bytes
    // therefore the location within
    // the major row is the lower 3
    // bits of the row number, the
    // rest is the major row number
    return (y & 7);
}

void lcd_writeChunk(char chunk)
{
  writeToLCD(LCD1202_DATA, chunk);
}

void lcd_writeChunkAddr(char chunk, u_char xAddr, u_char yAddr)
{
    // set address on LCD
    lcd_setAddr(xAddr, yAddr);
    
    // write display data to the LCD
    lcd_writeChunk(chunk);
}

