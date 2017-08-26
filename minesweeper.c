#include "minesweeper.h"
//#define MINESWEEPER

static u_char Flag_Counter = 0; // Total flags placed
static u_short Square_Counter = 64; //Tiles left uncovered
static u_short Flag_Array[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; //Flag not present
static u_short Mine_Array[8] = { 0, 0, 1, 0, 0, 0, 0, 0 }; //Mines not present
static u_short Tile_Status_Array[8] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }; //Tiles are set to hidden
static u_char GameBoard_Array[8][8] = {
	{ 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },//row 7
	{ 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },//row 6
	{ 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },//row 5
	{ 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },//row 4
	{ 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },//row 3
	{ 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },//row 2
	{ 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },//row 1
	{ 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } //row 0
};

void sub_Square_Counter(void)
{
  Square_Counter--;
}

void add_Flag_Counter(void)
{
  Flag_Counter++;
}

char getFlags(void){

  return 10 - Flag_Counter;
}

void sub_Flag_Counter(void)
{
  Flag_Counter--;
} 

u_short get_Mine_Array(u_char row)
{
	return Mine_Array[row];
}

u_short get_Square_Counter(void)
{
	return Square_Counter;
}

u_char flag_Eq_Mines(void)
{
	u_char counter;
	u_char equal_To_Counter;
	for (counter = equal_To_Counter = 0; counter < 8; counter++){
		if (BIT_EQUAL(Flag_Array[counter], Mine_Array[counter]))
			equal_To_Counter++;
	}
	return (equal_To_Counter == 8) ? 1 : 0;
}

void mine_Return(u_char row, u_char column)
{
	if (BIT_SET(Mine_Array[row], column))
		GameBoard_Array[column][row] = 0x7;
}

u_char get_Bit(u_char row, u_char column, u_char select)
{
	switch (select){
	case 1: return BIT_SET(Mine_Array[row], column); break;
	case 2: return BIT_SET(Tile_Status_Array[row], column); break;
	default: return BIT_SET(Flag_Array[row], column);
	}
}

u_short get_Bits(u_char row, u_char select)
{
	switch (select){
	case 1: return Mine_Array[row]; break;
	case 2: return Tile_Status_Array[row]; break;
	default: return Flag_Array[row];
	}
}

void set_Bit_State(u_char row, u_char column, u_char select)
{
	short tmp = 0;
	switch (column) {
	case 0: tmp = SET_BIT_0; break;
	case 1: tmp = SET_BIT_1; break;
	case 2: tmp = SET_BIT_2; break;
	case 3: tmp = SET_BIT_3; break;
	case 4: tmp = SET_BIT_4; break;
	case 5: tmp = SET_BIT_5; break;
	case 6: tmp = SET_BIT_6; break;
	case 7: tmp = SET_BIT_7; break;
	default: tmp = 0x0;
	}
	switch (select){
	case 1: SET_BIT(Mine_Array[row], tmp); break;
	case 2: SET_BIT(Tile_Status_Array[row], tmp); break;
	default: SET_BIT(Flag_Array[row], tmp);
	}
}

u_char get_Char_At(u_char row, u_char column)
{
	return GameBoard_Array[column][row];
}

void set_Char_At(u_char row, u_char column, u_char src)
{
	GameBoard_Array[column][row] = src;
	if(src == 7)
	  set_Bit_State(row,column,1);
}
