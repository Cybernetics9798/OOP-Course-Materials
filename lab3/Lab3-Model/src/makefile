CC = g++
CFLAGS = -I. -I../inc -g -std=c++11
OBJ = objPos.o objPosArrayList.o objPosDLinkedList.o objPosStack.o DLinkedList.o cmdQueue.o GameMechs.o MacUILib.o Player.o ItemBin.o ScreenDrawer.o MainGame.o  
DEPS = *.h

ifeq (${OS}, Windows_NT)
	OSSETTING = -DWINDOWS
else
	OSSETTING = -DPOSIX
	POSTLINKER = -lncurses   ## uncomment this if on Linux
endif

EXEC = Project

%.o: %.cpp $(DEPENDS)
	$(CC) ${OSSETTING} -c -o $@ $< $(CFLAGS)

${EXEC} : $(OBJ)
	$(CC) ${OSSETTING} -o $@ ${OBJ} $(CFLAGS) ${POSTLINKER}

clean :
	rm -rf ${OBJ} ${EXEC} ${EXEC}.exe

