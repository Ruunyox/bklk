#include "bklk.h"
#include <cstdlib>
#include <getopt.h>
#include <memory>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int fg = 7, bg = 0, ch, opt;
  bool flags = false;
  const char *clktype;

  while ((opt = getopt(argc, argv, "msl")) != -1) {
    switch (opt) {
    case 'l':
      flags = true;
      clktype = "reduced";
      fg = 0;
      bg = 7;
      break;
    case 's':
      clktype = "full";
      flags = true;
      break;
    case 'm':
      clktype = "reduced";
      flags = true;
      break;
    }
  }
  if (flags == false) {
    printf("bklk: usage & display options:\n\t-s\tseconds\n\t-m\tminutes");
    exit(1);
  }
  curses_init();
  auto clk = std::make_unique<binclock>(fg, bg, LINES, COLS, clktype);
  while (ch != 'q') {
    ch = getch();
    if (ch == 'c') {
      fg = (fg + 1) % 8;
      clk->updateColors(fg, bg);
      continue;
    }
    if (ch == KEY_RESIZE) {
      curses_init();
      clk = std::make_unique<binclock>(fg, bg, LINES, COLS, clktype);
    }
    clk->updateTime();
    clk->drawTime();
    usleep(50000);
  }
  endwin();
}
