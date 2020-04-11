STD=c++14
CC = g++
LIBS = -lncurses

all:
	${CC} -o bklk main.cpp ${LIBS} -std=${STD} 
	@echo "Done."
clean:
	rm *.o
