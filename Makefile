#
# Makefile - timer.elf
#
# @author Adrian Veliz
# @author Eric Freudenthal
# @modified Mathew Boston
# @version 0.1.20130910
#

all:board_demo.elf

# makfile configuration
COMMON_OBJECTS         =  lcd_backend.o lcd_utils.o sr.o
CPU             = msp430g2553 
CFLAGS          = -mmcu=${CPU} -Os -g 

#switch the compiler (for the internal make rules)
CC              = msp430-gcc
AS              = msp430-as

#additional rules for files
board_demo.elf: board_demo.o drawBoard.o drawPlayer.o face.o minesweeper.o logic.o ${COMMON_OBJECTS}
	msp430-gcc -mmcu=${CPU} -g -o $@ $^

install_board: board_demo.elf
	mspdebug rf2500 "prog $^"
clean:
	rm -f *.o *.elf *.h.gch
