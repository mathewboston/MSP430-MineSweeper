#include "drawBoard.h"
#include "face.h"

static const char cord[4] = { 64, 72, 80, 88 };

void drawFaceCool(void)
{
	smile();
	glasses();
}

void drawFaceShock(void)
{
	shock();
	eyes();
}

void drawFace(void)
{
	eyes();
	smile();
}

void drawFaceDead(void)
{
	cross();
	shock();
}

void glasses(void)
{
	int i;
	u_char smil1[8] = { 0x04, 0x1c, 0x3c, 0x6c, 0x6c, 0x6c, 0x3c, 0x1c };

	for (i = 0; i < 8; i++){
		lcd_writeChunkAddr(smil1[i], cord[1] + i, 3);
		lcd_writeChunkAddr(smil1[7 - i], cord[2] + i, 3);
	}
}

void cross(void)
{
	int i;
	u_char smil1[8] = { 0x00, 0x00, 0x00, 0x00, 0x81, 0x24, 0x24, 0x18 };

	for (i = 0; i < 8; i++){
		lcd_writeChunkAddr(smil1[i], cord[1] + i, 3);
		lcd_writeChunkAddr(smil1[7 - i], cord[2] + i, 3);
	}
}

void eyes(void)
{
	int i;
	u_char smil1[8] = { 0x00, 0x00, 0xe7, 0xff, 0xff, 0xe7, 0x00, 0x00 };

	for (i = 0; i < 8; i++){
		lcd_writeChunkAddr(smil1[i], cord[1] + i, 3);
		lcd_writeChunkAddr(smil1[7 - i], cord[2] + i, 3);
	}
}

void shock(void)
{
	int i;
	u_char smil1[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x66, 0x62 };

	for (i = 0; i < 8; i++){
		lcd_writeChunkAddr(smil1[i], cord[1] + i, 4);
		lcd_writeChunkAddr(smil1[7 - i], cord[2] + i, 4);
	}
}

void smile(void)
{
	int i;
	u_char smil1[8] = { 0x00, 0x0c, 0x18, 0x10, 0x30, 0x40, 0x40, 0x40 };

	for (i = 0; i < 8; i++){
		lcd_writeChunkAddr(smil1[i], cord[1] + i, 4);
		lcd_writeChunkAddr(smil1[7 - i], cord[2] + i, 4);
	}
}
