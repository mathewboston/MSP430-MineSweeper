#ifndef booster1202_included
#define booster1202_included

#include "STE2007.h"

// comment out for software SPI
#define HARDWARE_SPI

// LCD pins
#define LCD1202_SCLK_PIN BIT5  // P1
#define LCD1202_MOSI_PIN BIT7 // P1
#define LCD1202_CS_PIN BIT0 // P1
#define LCD1202_BACKLIGHT_PIN BIT4 // P1
#define LCD1202_RESET_PIN BIT0 // P2

// switches
#define SW1 BIT3 // on far right...
// direction pad...
#define SW2 BIT2 // P2 left switch
#define SW3 BIT3 // P2 down switch
#define SW4 BIT4 // P2 up switch
#define SW5 BIT1 // P2 right switch

//
#define LCD1202_SELECT P1OUT &= ~LCD1202_CS_PIN
#define LCD1202_DESELECT P1OUT |= LCD1202_CS_PIN
#define LCD1202_RESET_LO P2OUT &= ~LCD1202_RESET_PIN
#define LCD1202_RESET_HI P2OUT |= LCD1202_RESET_PIN
#define LCD1202_MOSI_HI P1OUT |= LCD1202_MOSI_PIN
#define LCD1202_MOSI_LO P1OUT &= ~LCD1202_MOSI_PIN
#define LCD1202_COMMAND_WITH_ARGS 2
#define LCD1202_COMMAND 0
#define LCD1202_DATA 1
#define LCD1202_CLOCK P1OUT |= LCD1202_SCLK_PIN; P1OUT &= ~LCD1202_SCLK_PIN
#define LCD1202_DISABLE_HARDWARE_SPI  P1SEL &= ~(LCD1202_SCLK_PIN + LCD1202_MOSI_PIN); P1SEL2 &= ~(LCD1202_SCLK_PIN + LCD1202_MOSI_PIN)
#define LCD1202_ENABLE_HARDWARE_SPI P1SEL |= LCD1202_SCLK_PIN + LCD1202_MOSI_PIN; P1SEL2 |= LCD1202_SCLK_PIN + LCD1202_MOSI_PIN


typedef unsigned char u_char;

#endif // booster1202_included
