#ifndef lcd_char_included

#define lcd_char_included
#include "lcd_utils.h"

/* functions to write strings and characters to the lcd */
void drawBoard();
void drawCell(u_char xLoc,u_char yMajor);
void highlight(u_char x,u_char y);
void lowlight(u_char x, u_char y);
void showCell(u_char x, u_char y);
void drawTime(int time);
void drawNum(int number,u_char x,u_char yMajor);
#endif // lcd_char_included
