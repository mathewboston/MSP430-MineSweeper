//#ifndef MINESWEEPER
#include "booster1202.h"
 
#define SET_BIT_7 128
#define SET_BIT_6 64
#define SET_BIT_5 32
#define SET_BIT_4 16
#define SET_BIT_3 8
#define SET_BIT_2 4
#define SET_BIT_1 2
#define SET_BIT_0 1

#define SET_BIT(dest, src) (dest ^= src)
#define BIT_EQUAL(bit_a, bit_b) (bit_a == bit_b)
#define BIT_SET(src, offset) (src & (1<<offset))

//typedef unsigned char u_char;
typedef unsigned short u_short;

/*
extern u_char Flag_Counter;
extern u_short Square_Counter; 
extern u_short Flag_Array[8];
extern u_short Mine_Array[8];
extern u_short Tile_Status_Array[8];
extern u_char GameBoard_Array[8][8];
*/

void sub_Square_Counter(void);
void add_Flag_Counter(void);
char getFlags(void);
void sub_Flag_Counter(void);
u_short get_Mine_Array(u_char row);
u_short get_Tile_Counter(void);
u_char flag_Eg_Mines(void);
void mine_Return(u_char row, u_char column);
u_char get_Bit(u_char row, u_char column, u_char select);
u_short get_Bits(u_char row, u_char select);
void set_Bit_State(u_char row, u_char column, u_char select);
u_char get_Char_At(u_char row, u_char column);
void set_Char_At(u_char row, u_char column, u_char src);

//#endif
