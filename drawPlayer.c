#include "drawBoard.h"
#include "minesweeper.h"
/*fix the move function*/
short local = 0;
u_char ISON = 0;

void show(u_char x, u_char y)
{
	unsigned char type = get_Char_At(x, y);
	if (get_Bit(x, y, 2)){
		drawCell(x, y);
		return;
	}
	if (type >= 8 || type == 0){
		clearCell(x, y);
		return;
	}
	else if (type == 6){
		drawFlagMine(1, x, y); return;
	}
	else if (type == 7){//mine
		drawFlagMine(0, x, y); return;
	}
	else
		drawNum(type, x * 8, y);
}

void drawPep(u_char x,u_char y){
  if(x>=8||x<0)
    return;
  if(y>=8||y<0)
    return; 
 u_char player[8]={0xff,0x98,0x9e,0xf9,0xf9,0x9e,0x98,0xff};
  int i;
  x=x*8;
  for (i = 0; i < 8; i++)
      lcd_writeChunkAddr(player[i], x + i, y);

}
void blink()
{
	u_char x;
	u_char y;
	u_char xy;
	if ((local & 64) >= 64){
		local -= 64;
		xy = local;
		ISON = 0;
	}
	else{
		xy = local;
		local += 64;
		ISON = 1;
	}
	y = (xy & 56);
	y = y >> 3;
	x = (xy & 7);
	if (ISON)
		drawPep(x, y);
	else
		show(x, y);
}

void moveTo(u_char x, u_char y)
{

	u_char xy = local;
	u_char xl, yl;
	yl = (xy & 56);
	yl >> 3;
	xl = (xy & 7);
	show(xl, yl);
	local = (y << 3);
	local |= x;
}
