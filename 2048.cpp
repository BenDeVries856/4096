#include <stdlib.h>
#include <ncurses.h>

const int width = 10;
const int height = 10;
int background[width*height];

int main(){

  /* INITIALIZE */
  // determines terminal type, sets up ncurses environment
  initscr();

  // disables line buffering
  cbreak();

  // disables echoing input back to screen
  noecho();

  // clears the screen
  clear();

  int x, y;
  for(y = 0; y < height; y++){
    for(x = 0; x < width * 3; x += 3){
      mvaddch(y, x, '0');
      mvaddch(y, x+1, ' ');
      mvaddch(y, x+2, ' ');
    }
  }

  // display changes to the screen
  refresh();

  // close program when the user presses a key
  getch();
  endwin();

  return 0;
}
