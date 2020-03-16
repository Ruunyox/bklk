#include "bklk.h"
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <memory>

int main(int argc, char **argv) {
	int fg = 7, bg = 0, ch, opt;
	bool flags=false;
	const char* clktype;
	
	while((opt = getopt(argc,argv,"msl")) != -1) {
		switch(opt) {
		case 'l':
			flags=true;
			fg = 0;
			bg = 7;
			break;
		case 's':
			clktype = "full";
			flags=true;
			break;
		case 'm':
			clktype = "reduced";
			flags=true;
			break;
		}
	}
	if(flags==false) {
			printf("bklk: usage & display options:\n\t-s\tseconds\n\t-m\tminutes");
			exit(1);
	}
	curses_init();
	std::unique_ptr <binclock> clk (new binclock(fg,bg,LINES,COLS,clktype));
	while(ch != 'q') {
		ch = getch();
		if(ch == 'c'){
			fg = (fg + 1)%8;
			clk->updateColors(fg,bg);	
			continue;
		}
        if(ch == KEY_RESIZE) {
            curses_init();
            clk.reset(new binclock(fg,bg,LINES,COLS,clktype));
        }
		clk->updateTime();
		clk->drawTime();
		usleep(50000);
	}
	endwin();
}
