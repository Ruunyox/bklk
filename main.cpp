#include "bklk.h"
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <memory>

int main(int argc, char **argv) {
	int fg = 7, rows, cols,ch,opt;
	bool flags=false;
	const char* clktype;
	
	while((opt = getopt(argc,argv,"ms")) != -1) {
		switch(opt) {
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
	cursesInit();
	std::unique_ptr <binclock> clk (new binclock(fg,-1,LINES,COLS,clktype));
	while(ch != 'q') {
		ch = getch();
		if(ch == 'c'){
			fg = (fg + 1)%8;
			clk->updateColors(fg,-1);	
			continue;
		}
		clk->updateTime();
		clk->drawTime();
		usleep(50000);
	}
	printf("%s",argv[1]);
	endwin();
}
