#include <msp430g2553.h>
#include "lcd_utils.h"
#include "logic.h"
#include "drawBoard.h"
#include "drawPlayer.h"
#include "face.h"
#include "minesweeper.h"

#define Button_Held_State 1
#define Button_Released_State 0
#define End_Game_State 0
#define Game_In_Progress 1

/* global vars */
u_char x = 0;
u_char y = 0;
u_char Button_State_Machine = Button_Released_State;
u_char Game_State_Machine = Game_In_Progress;

void mcOsc1MHz(void) 		/* set master clock to 1MHz */
{
	BCSCTL1 = CALBC1_1MHZ;   // Set range 
	DCOCTL = CALDCO_1MHZ;
	BCSCTL2 &= ~(DIVS_3);    // SMCLK = DCO / 8 = 1MHz 
}

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;     // Stop watchdog timer
	lcdinit();                    // init LCD (also: CPU clock to 16MHz)
	lcd_setAddr(0, 3);
	CCTL0 = CCIE;                 // CCR0 interrupt enabled
	TACTL = TASSEL_2 + MC_1 + ID_3; // Set timer clock to CPU clock/8
	CCR0 = 50000;			// Interrupt every 10 ms
	setMines();                    //Initialize
	counter();
	drawBoard();
	or_sr(0x18);			// CPU off, GIE on
}

/* far right switch */
interrupt(PORT1_VECTOR) Port_1(void)
{
	// clear switch interrupt pending
 	P1IFG &= ~SW1;
	P2IFG &= ~(SW2 + SW3 + SW4 + SW5);
	if(Game_State_Machine){
	  drawBoard();
	  Button_State_Machine = Button_Held_State;
	}
	//showLose();//debug
}

void clear_Tile(void)
{
  if(get_Bit(x,y,0)){
    set_Bit_State(x, y, 2);
    show(x, y);
  }else{
    sub_Square_Counter();
    set_Bit_State(x, y, 2);
    show(x, y);
  }
}

void check_End_Game(void)
{
  if(lose(x,y) & (get_Bit(x,y,0)==0)){
    showLose();
    drawFaceDead();
    Game_State_Machine = End_Game_State;
  }else if(flag_Eq_Mines()){
    drawFaceCool();
    Game_State_Machine = End_Game_State;
  }
}

/* direction pad */
interrupt(PORT2_VECTOR) Port_2(void)
{
	P1IFG &= ~SW1;          // clear interrupt from right hand Switch on P1 
	P2IFG &= ~(SW2 + SW3 + SW4 + SW5); // clear interrupts from direction switches (on port 2)
	if(Game_State_Machine){
	  drawBoard();
	if (!(P2IN & SW2)){ //left
		if (x == 0)	x = 7;
		else
			x--;
	}
	else if (!(P2IN & SW5)){ //right
		if (x == 7)	x = 0;
		else
			x++;
	}
	else if (!(P2IN & SW3)){ //down
		if (y == 7)	y = 0;
		else
			y++;
	}
	else if (!(P2IN & SW4)){ //up
		if (y == 0)	y = 7;
		else
			y--;
	}
	moveTo(x, y);
	}

}
static char time=0;
/* timer interrupt */
interrupt(TIMER0_A0_VECTOR) Timer_0(void)
{
	static short clockDivide = 0;
	static short buttonHold = 0;
	static short timeinc=0;
	
	if (clockDivide++ > 20) {
	  blink();
	  clockDivide = 0;
	  timeinc++;
	  
	}
	if(timeinc>2){
	  drawTime(time++);
	  timeinc=0;
	}
	drawScore(getFlags());
	if(Button_State_Machine)
	  buttonHold++;
	if (buttonHold == 50 ){
	  set_Bit_State(x, y, 0);
	  if(get_Char_At(x,y) != 6 && getFlags() != 0){
	    add_Flag_Counter();
	    set_Char_At(x, y, 6);
	  }
	  else{
	    set_Char_At(x,y,0);
	    sub_Flag_Counter();
	  }
	  buttonHold = 0;
	  show(x, y);
	}
	else if ((!(P1IN & SW1) == 0) & Button_State_Machine){
		drawFaceShock();
		Button_State_Machine = Button_Released_State;
		clear_Tile();
		check_End_Game();
		buttonHold = 0;
	}
}
