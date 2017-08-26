Konani Error readme file: Amber Gomez, Mathew Boston, Lee Curry

Minesweeper is a game where the player detects mines by clicking on a box. If the player suspects a box to be a mine, they can place a flag down over that spot. Othewise, the value underneath will be revealed. Each revealed box is labled with a number representing the amount of mines that surround it. If the player has selected a mine, the game is over. There are ten mines in totatl and if the player can correctly select every box except for the mines, then they win. 

In order to run minesweeper on the MS430, the command "make install_c" will download the files onto the device. Once the program loads onto the device, the left buttons can be used to navigate through the board and the right can be used to place a flag or select a box. 

The following classes play a role in creating minesweeper. 

1 Board.c
2 Board_demo.c
3 drawBoard.c
4 drawPlayer.c
5 face.c- contains a face that will be displayed on the MSP430. If the plaer clicks on a space, the face will changed to shocked. If the player clicks on a bomb, the smiley face will turn into a dead one. 
6 lcd_backend.c
7 lcd_utils.c
8 logic.c- contains data such as where to place the mines, how to detect a winner and a loser, and how many mines surround a square.
9 minesweeper.c
