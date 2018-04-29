CC = g++
LIBS = -lncurses

all:
	${CC} -o bklk main.cpp ${LIBS}  

clean:
	rm *.o
