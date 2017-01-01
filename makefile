CC = gcc

FILES = sharedMem.c master.c
FLAGS = -Wall -w
OBJ = sharedMem.o master.o
OUT_EXEC = memChildShare.out

build:$(OBJ)
	$(CC) $(FLAGS) $(FILES) -o $(OUT_EXEC)

clean:	
	rm -f *.o

rebuild: clean	build