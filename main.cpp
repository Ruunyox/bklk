#include "bklk.h"
#include <unistd.h>
#include <string.h>

#if USE_SIGWINCH
        CatchIfDefault(SIGWINCH, handle_SIGWINCH);
#endif

int main(int argc, char **argv) {
	int fg = 7, rows, cols;
	int ch;
	cursesInit();
	binclock clk(fg,-1,LINES,COLS,"full");
	while(ch != 'q') {
		ch = getch();
		if(ch == 'c'){
			fg = (fg + 1)%8;
			binclock clk(fg,-1,LINES,COLS,"full");
			continue;
		}
		if(ch == KEY_RESIZE){
			cursesInit();
			getmaxyx(stdscr,rows,cols);
			wresize(stdscr,rows,cols);
			binclock clk(fg,-1,rows,cols,"full");
			continue;
		}
		clk.updateTime();
		clk.drawTime();
		usleep(50000);
	}
	endwin();
}
