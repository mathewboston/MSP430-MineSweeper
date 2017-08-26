#include "minesweeper.h"
//#include <stdlib.h>
#include "logic.h"

void setMines(void)
{
  set_Char_At(7,2,7);//1
  set_Char_At(2,5,7);//2
  set_Char_At(2,6,7);//3
  set_Char_At(1,3,7);//4
  set_Char_At(6,7,7);//5
  set_Char_At(5,7,7);//6
  set_Char_At(4,6,7);//7
  set_Char_At(1,4,7);//8
  set_Char_At(0,1,7);//9
  set_Char_At(3,3,7);//10
  /*  
	char x;
	char y;
	char i;
	for (i = 0; i < 8; i++){
	  //x = rando;
	  //	y = rando;
	  x = i;
	  y = i;
		if (get_Char_At(x, y) == 0){
		  set_Bit_State(x,y,1);
		  set_Char_At(x, y, 7);
		}
		//else
		//	--i;
			}*///sets bombs randomly on the board
}//The random method had a few errors in it, so we decided to select where the mines would go. 

void counter(void)
{
	char j, i;
	for (i = 0; i < 8; i++){
		for (j = 0; j < 8; j++){
			//char temp = get_Char_At(i, j);
			if (get_Char_At(i, j) != 7)//not a bomb
				set_Char_At(i, j, (get_Char_At(i, j) + around(i, j)));
		}
	}//will assign the number of bombs around each space
}

char around(char i, char j)
{
	char num = get_Char_At(i, j);
	if (num == 7)
		return 0;//if your current space is a bomb, add nothing.
	else{
		num = 0;
		if (get_Char_At(i - 1, j - 1) == 7 && i - 1 >= 0 && j - 1 >= 0)
			num += 1;//topleft
		if (get_Char_At(i, j - 1) == 7 && i >= 0 && j - 1 > 0)
			num += 1;//topmid
		if (get_Char_At(i + 1, j - 1) == 7 && i + 1 < 8 && j - 1 >= 0)
			num += 1;//topright
		if (get_Char_At(i - 1, j) == 7 && i - 1 >= 0 && j >= 0)
			num += 1;//midleft
		if (get_Char_At(i + 1, j) == 7 && i + 1 < 8 && j >= 0)
			num += 1;//midright
		if (get_Char_At(i - 1, j + 1) == 7 && i - 1 >= 0 && j + 1 < 8)
			num += 1;//botleft
		if (get_Char_At(i, j + 1) == 7 && i >= 0 && j + 1 < 8)
			num += 1;//botmid
		if (get_Char_At(i + 1, j + 1) == 7 && i + 1 < 8 && j + 1 < 8)
			num += 1;//botright
	}//else
	return num;
}//calculates number of bombs around a space

char win(void)
{
  if (get_Square_Counter() == 10)
		return 1;
	return flag_Eq_Mines();
}

char lose(char i, char j)
{
  //return BIT_SET(get_Mine_Array(i), j);
  return (get_Char_At(i,j)==7);
}
