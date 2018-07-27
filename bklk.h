#include <ncurses.h>
#include <stdio.h>
#include <ctime>
#include <iostream>

#define BUFSZ 80

void cursesInit(void){
    initscr();
    start_color();
	use_default_colors();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr,TRUE);
    keypad(stdscr,TRUE);
}

class binclock {
	public:
	
	int sizey,sizex,fg;
	const char *type;
	time_t t;
	char tstring[BUFSZ]; 
	struct tm *timenow;
	int digits[6];
	int *mask;	
	
	binclock(int i_fg, int i_bg, int rows, int cols,const char *i_type = "full") {
		init_pair(1,i_fg,i_bg);
		init_pair(2,0,i_bg);
		type = i_type;
		sizey = rows; sizex = cols;
		mask = (int* )malloc(sizeof(int));
	}

	~binclock() {
		delete[] mask;
		delete timenow;
	}

	void updateColors(int i_fg, int i_bg) {
		init_pair(1,i_fg,i_bg);
		init_pair(2,0,i_bg);
	}
	
	void updateTime() {
		t = time(0);
		timenow = localtime(&t);
		digits[0] = (timenow->tm_hour/10);
		digits[1] = (timenow->tm_hour- digits[0]*10);
		digits[2] = (timenow->tm_min/ 10);	
		digits[3] = (timenow->tm_min- digits[2]*10);	
		digits[4] = (timenow->tm_sec/ 10);	
		digits[5] = (timenow->tm_sec- digits[4]*10);	
	} 
	
	int* mkMask(int in, int *mask){
		if(in == 0){mask[0]=0;mask[1]=0;mask[2]=0;mask[3]=0;}	
		if(in == 1){mask[0]=1;mask[1]=0;mask[2]=0;mask[3]=0;}	
		if(in == 2){mask[0]=0;mask[1]=1;mask[2]=0;mask[3]=0;}	
		if(in == 3){mask[0]=1;mask[1]=1;mask[2]=0;mask[3]=0;}	
		if(in == 4){mask[0]=0;mask[1]=0;mask[2]=1;mask[3]=0;}	
		if(in == 5){mask[0]=1;mask[1]=0;mask[2]=1;mask[3]=0;}	
		if(in == 6){mask[0]=0;mask[1]=1;mask[2]=1;mask[3]=0;}	
		if(in == 7){mask[0]=1;mask[1]=1;mask[2]=1;mask[3]=0;}	
		if(in == 8){mask[0]=0;mask[1]=0;mask[2]=0;mask[3]=1;}	
		if(in == 9){mask[0]=1;mask[1]=0;mask[2]=0;mask[3]=1;}	
		return mask;
	}

	void drawTime() {
		int k = 0;
		clear();
		for(int j=0;j<6;j++){
			if(j%2 == 0){
				k++;	
			}
			mask = mkMask(digits[j],mask);
			for(int i=0;i<4;i++){
				if(mask[i] == 1){
					attron(A_REVERSE  | COLOR_PAIR(1));
					mvaddstr(4+(sizey)/2-2*i,(sizex-42)/2+(4*j)+5*k,"  ");
					attroff(A_REVERSE | COLOR_PAIR(1));
				}
				else {
					attron(A_REVERSE  | COLOR_PAIR(2));
					mvaddstr(4+(sizey)/2-2*i,(sizex-42)/2+(4*j)+5*k,"  ");
					attroff(A_REVERSE | COLOR_PAIR(2));
					attron(COLOR_PAIR(1));
				}
			}
		}
		strftime(tstring,BUFSZ-1,"%a %b %d",timenow);
		attron(COLOR_PAIR(1));
		mvaddstr(sizey/2-4,sizex/2-5,tstring);
		refresh();	
	}
};
