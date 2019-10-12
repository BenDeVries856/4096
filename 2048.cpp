#include <stdlib.h>
#include <ncurses.h>
#include <ctime>

const int width = 10;
const int height = 10;
char background[width*height];

void clearBackground(char *bg, int s){
  unsigned int i;
  for(i = 0; i < s; i++){
    bg[i] = '.';
  }
}

void placeTile(char *bg, int s){
  unsigned int i, ii;
  ii = 0;
  do{
    i = rand() % s + 1;
    ii++;
  }while(bg[i] != '.' && ii <= 999);
  bg[i] = '1';
}

void displayBackground(char *bg, int w, int h){
  unsigned int x, y;
  unsigned int xx = 0;
  for(y = 0; y < h; y++){
    for(x = 0; x < w * 3; x += 3){
      mvaddch(y, x, bg[y*w+xx]);
      mvaddch(y, x+1, ' ');
      mvaddch(y, x+2, ' ');
      xx++;
    }
    xx = 0;
  }
}

void moveUp(char *bg, int w, int h){
  int x, y;
  for(y = 1; y < h; y++){
    for(x = 0; x < w; x++){
      if(bg[y*w+x] != '.'){
        if(bg[(y-1)*w+x] == '.'){
	  bg[(y-1)*w+x] = bg[y*w+x];
	  bg[y*w+x] = '.';
	}else if(bg[(y-1)*w+x] == bg[y*w+x]){
	  bg[(y-1)*w+x]++;
	  bg[y*w+x] = '1';
	}
      }
    }
  }
}

void moveDown(char *bg, int w, int h){
  int x, y;
  for(y = h-2; y >= 0; y--){
    for(x = 0; x < w; x++){
      if(bg[y*w+x] != '.'){
        if(bg[(y+1)*w+x] == '.'){
	  bg[(y+1)*w+x] = bg[y*w+x];
	  bg[y*w+x] = '.';
	}else if(bg[(y+1)*w+x] == bg[y*w+x]){
	  bg[(y+1)*w+x]++;
	  bg[y*w+x] = '.';
	}
      }
    }
  }
}

void moveLeft(char *bg, int w, int h){
  int x, y;
  for(y = 0; y < h; y++){
    for(x = 1; x < w; x++){
      if(bg[y*w+x] != '.'){
        if(bg[y*w+x-1] == '.'){
	  bg[y*w+x-1] = bg[y*w+x];
	  bg[y*w+x] = '.';
	}else if(bg[y*w+x-1] == bg[y*w+x]){
	  bg[y*w+x-1]++;
	  bg[y*w+x] = '.';
	}
      }
    }
  }
}

void moveRight(char *bg, int w, int h){
  int x, y;
  for(y = 0; y < h; y++){
    for(x = w-2; x >= 0; x--){
      if(bg[y*w+x] != '.'){
        if(bg[y*w+x+1] == '.'){
	  bg[y*w+x+1] = bg[y*w+x];
	  bg[y*w+x] = '.';
	}else if(bg[y*w+x+1] == bg[y*w+x]){
	  bg[y*w+x+1]++;
	  bg[y*w+x] = '.';
	}
      }
    }
  }
}

int main(){

  int ch;

  // initialize sequence of random numbers
  srand(time(NULL));

  /* INITIALIZE */
  // determines terminal type, sets up ncurses environment
  initscr();

  // enable keyboard
  keypad(stdscr, TRUE);

  // disables line buffering
  cbreak();

  // disables echoing input back to screen
  noecho();

  // clears the screen
  clear();
  clearBackground(background, sizeof(background));

  do{
    
    // determine which key the user pressed and move the tiles accordingly
    switch(ch){
      case KEY_UP:
        moveUp(background, width, height);
	break;
      case KEY_DOWN:
	moveDown(background, width, height);
	break;
      case KEY_LEFT:
	moveLeft(background, width, height);
	break;
      case KEY_RIGHT:
	moveRight(background, width, height);
	break;
    }

    // place a new tile and write to screen
    placeTile(background, sizeof(background));
    displayBackground(background, width, height);

    // display changes to screen
    refresh();

    // get user input
    ch = getch();
  }while((ch != 'q') && (ch != 'Q'));

  // close the program
  endwin();

  return 0;
}
