#ifndef lcd_char_included

#define lcd_char_included
#include "lcd_utils.h"

/* functions to write strings and characters to the lcd */
void blink();
void show();
void drawPep(u_char x, u_char y);
void moveTo(u_char x,u_char y);
#endif // lcd_char_included
