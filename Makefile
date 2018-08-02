CC = g++
LIBS = -lncurses

all:
	${CC} -o bklk main.cpp ${LIBS}  
	@echo "Done."
clean:
	rm *.o
