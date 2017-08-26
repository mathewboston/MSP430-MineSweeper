#ifndef lcd_backend_included
#define lcd_backend_included

#define interrupt(x) void __attribute__((interrupt (x)))

/* initalizes the lcd */
void lcdinit();
/* writes to the lcd */
void writeToLCD(u_char dataCommand, char data);
/* blanks the lcd */
void lcdclear();
/* sets the lcds contrast */
void lcdsetContrast(u_char contrast);

// Screen Size
#define MAX_X 96
#define MAX_Y 68

#endif // lcd_backend_included
