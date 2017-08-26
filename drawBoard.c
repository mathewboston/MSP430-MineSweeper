#include "drawBoard.h"
#include "minesweeper.h"

static const char locx[9] = { 0, 8, 16, 24, 32, 40, 48, 56 };
static const char timeCor[4] = { 64, 72, 80, 88 };
static const u_char flag[8] = { 0x00, 0x40, 0x40, 0x7e, 0x4c, 0x48, 0x40,0x00 };
static const u_char numb[11][7] = {
	{ 0x00, 0x3e, 0x51, 0x49, 0x45, 0x3e, 0x00 }, // 30 0
	{ 0x00, 0x00, 0x42, 0x7f, 0x40, 0x00, 0x00 }, // 31 1
	{ 0x00, 0x42, 0x61, 0x51, 0x49, 0x46, 0x00 }, // 32 2
	{ 0x00, 0x21, 0x41, 0x45, 0x4b, 0x31, 0x00 }, // 33 3
	{ 0x00, 0x18, 0x14, 0x12, 0x7f, 0x10, 0x00 }, // 34 4
	{ 0x00, 0x27, 0x45, 0x45, 0x45, 0x39, 0x00 }, // 35 5
	{ 0x00, 0x3c, 0x4a, 0x49, 0x49, 0x30, 0x00 }, // 36 6
	{ 0x00, 0x01, 0x71, 0x09, 0x05, 0x03, 0x00 }, // 37 7
	{ 0x00, 0x36, 0x49, 0x49, 0x49, 0x36, 0x00 }, // 38 8
	{ 0x00, 0x06, 0x49, 0x49, 0x29, 0x1e, 0x00 } // 39 9
};

void drawNum(int number, u_char x, u_char yMajor)
{
	int i = 0;
	for (i = 0; i < 7; i++){
		u_char chunk = numb[number][i];
		lcd_writeChunkAddr(chunk, x + i, yMajor);
	}
}

void clearCell(u_char x, u_char y)
{
	int i;
	x = locx[x];
	lcd_writeChunkAddr(0x00u, x, y);
	lcd_writeChunkAddr(0x00u, x + 7, y);
	lcd_writeChunkAddr(0x7e, x + 1, y);
	lcd_writeChunkAddr(0x7e, x + 6, y);
	for (i = 2; i < 6; i++)
		lcd_writeChunkAddr(0x44, x + i, y);
}

void drawScore(int score)
{
	int i;
	for (i = 3; i >= 0; i--){
		drawNum(score % 10, timeCor[i], 7);
		score /= 10;
	}
}

void drawTime(int time)
{
	int i;
	for (i = 3; i >= 0; i--){
		drawNum(time % 10, timeCor[i], 0);
		time /= 10;
	}
}

void drawFlagMine(u_char isFlag, u_char x, u_char y)
{
	char i;
	x = locx[x];
	for (i = 0; i < 8; i++)
		if ((isFlag == 0) && i>3)
		  if(i!=7)
		    lcd_writeChunkAddr(0x40, x + i, y);//flag
		  else 
		    lcd_writeChunkAddr(0x00,x+1,y);
		else
			lcd_writeChunkAddr(flag[i], x + i, y);//mine
}
void lowlight(u_char x, u_char y)
{
	x = locx[x];
	lcd_writeChunkAddr(0x00u, x, y);
	lcd_writeChunkAddr(0x00u, x + 7, y);
}

void highlight(u_char x, u_char y)
{
	x = locx[x];
	lcd_writeChunkAddr(0xffu, x, y);
	lcd_writeChunkAddr(0xffu, x + 7, y);
}

void drawCell(u_char xLoc, u_char yMajor)
{
	if (yMajor < 8)
	{
		u_char chunk = 0x00u;
		u_char chnk = 0x7eu;

		u_char tem = locx[xLoc];
		lcd_writeChunkAddr(chunk, tem, yMajor);
		int i;
		for (i = 1; i < 7; i++){
			tem++;
			lcd_writeChunkAddr(chnk, tem, yMajor);
		}
		tem++;
		lcd_writeChunkAddr(chunk, tem, yMajor);
	}
}

void showLose()
{
	int x, y;
	for (x = 0; x < 8; x++)
		for (y = 0; y < 8; y++)
			showCell(x, y);
}

void showCell(u_char x, u_char y)
{
	unsigned char type = get_Char_At(x, y);

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

void drawBoard()
{
	u_char x = 0;
	u_char y = 0;

	for (x = 0; x < 8; x++)
		for (y = 0; y < 8; y++)
			show(x, y);
	drawScore(0);
	drawFace();
	drawTime(0);
}
