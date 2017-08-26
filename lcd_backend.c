
#include "booster1202.h"
#include "lcd_backend.h"

#include "msp430g2553.h"
#include "STE2007.h"

void lcdinit(void)
{
  WDTCTL = WDTPW + WDTHOLD;	// disable WDT
  BCSCTL1 = CALBC1_16MHZ;	// 16MHz clock
  DCOCTL = CALDCO_16MHZ;

  // Configure pins to LCD
  P1OUT |= LCD1202_CS_PIN + LCD1202_BACKLIGHT_PIN + LCD1202_SCLK_PIN
    + LCD1202_MOSI_PIN;
  P1DIR |= LCD1202_CS_PIN + LCD1202_BACKLIGHT_PIN + LCD1202_SCLK_PIN
    + LCD1202_MOSI_PIN;

  P2OUT |= LCD1202_RESET_PIN;
  P2DIR |= LCD1202_RESET_PIN;

#ifdef HARDWARE_SPI
  // setup USIB
  P1SEL |= LCD1202_SCLK_PIN + LCD1202_MOSI_PIN;
  P1SEL2 |= LCD1202_SCLK_PIN + LCD1202_MOSI_PIN;

  UCB0CTL0 |= UCCKPH + UCMSB + UCMST + UCSYNC;	// 3-pin, 8-bit SPI master
  UCB0CTL1 |= UCSSEL_2;	// SMCLK
  UCB0BR0 |= 0x01;	// 1:1
  UCB0BR1 = 0;
  UCB0CTL1 &= ~UCSWRST;
#endif

  // Configure Switch on P1 & P2 //
  P1REN |= SW1; // Resistor ENable
  P2REN |= SW2 + SW3 + SW4 + SW5;
  P1IE |=  SW1; // Interrupt Enable
  P2IE |= SW2 + SW3 + SW4 + SW5;
  P1IES |= SW1; // Interrupt Enable Sensitive to high->low transition
  P2IES |= SW2 + SW3 + SW4 + SW5;
  // clear switch interrupt pending
  P1IFG &= ~SW1; 
  P2IFG &= ~(SW2 + SW3 + SW4 + SW5);
  __bis_SR_register(GIE);


  // startup the LCD
  LCD1202_RESET_LO;

  // This is critical it allows the
  // LCD time to reset if this is
  // removed or optimized out the
  // LCD will not power up properly
  int i;
  for (i = 0; i < 25; i++)
    __delay_cycles(64000);
  LCD1202_RESET_HI;
  for (i = 0; i < 25; i++)
    __delay_cycles(64000);

  writeToLCD(LCD1202_COMMAND, STE2007_RESET);
  writeToLCD(LCD1202_COMMAND, STE2007_DISPLAYALLPOINTSOFF);
  writeToLCD(LCD1202_COMMAND,
	     STE2007_POWERCONTROL | STE2007_POWERCTRL_ALL_ON);
  writeToLCD(LCD1202_COMMAND, STE2007_DISPLAYNORMAL);
  writeToLCD(LCD1202_COMMAND, STE2007_DISPLAYON);
	
	
  lcdsetContrast(0x17);
  lcdclear();
}


void writeToLCD(u_char dataCommand, char data) {
  LCD1202_SELECT;

#ifdef HARDWARE_SPI
  LCD1202_DISABLE_HARDWARE_SPI
    ;
  (dataCommand == LCD1202_DATA) ? (LCD1202_MOSI_HI) : (LCD1202_MOSI_LO);
  LCD1202_CLOCK
    ;
  LCD1202_ENABLE_HARDWARE_SPI
    ;
  UCB0TXBUF = data;
  while (UCB0STAT & UCBUSY)
    ;
#else
  (dataCommand == LCD1202_DATA) ? (LCD1202_MOSI_HI) : (LCD1202_MOSI_LO);
  LCD1202_CLOCK
    ;
  char c = 0;
  while (c < 8) {
    (data & 0x80) ? (LCD1202_MOSI_HI) : (LCD1202_MOSI_LO);
    LCD1202_CLOCK
      ;
    data <<= 1;
    c++;
  }
#endif

  //if (dataCommand != LCD1202_COMMAND_WITH_ARGS) // this is needed only for commands with args
  LCD1202_DESELECT;
}

/* sets the next address to write to */
void lcd_setAddr(u_char x, u_char yMajor)
{
  writeToLCD(LCD1202_COMMAND, STE2007_PAGEADDR | (yMajor & 0x0F));
  writeToLCD(LCD1202_COMMAND, STE2007_COLUADDR | (x >> 4));
  writeToLCD(LCD1202_COMMAND, STE2007_COLLADDR | (x & 0x0F));
}

/* blanks the lcd */
void lcdclear()
{
  /*int x, y;
  for (x = 0; x <= MAX_X; x++)
    for (y = 0; y <= MAX_Y >> 3; y++)
      lcdSetPixelByte((char) 0x00, x, y);*/
     
  lcd_setAddr(0, 0);
  int c = 0;
  while (c < STE2007_MAXBYTES) {
    writeToLCD(LCD1202_DATA, 0);
    c++;
  }
  lcd_setAddr(0, 0);
}

/* sets the contrast */
void lcdsetContrast(u_char contrast)
{
  writeToLCD(LCD1202_COMMAND, STE2007_ELECTRONICVOLUME | (contrast & 0x1F));
}

