#include <stdio.h>   // for standard input output functions
#include <ncurses.h>  // allows for window creation, cursor movement and keyboard input
#include <stdlib.h>  // used for rand function for fruit spawning
#include <unistd.h> // for usleep function used to delay program execution

void main() {

  WINDOW * win= initscr();     // initializes terminal screen

    keypad(win, true);   // Enables keyboard input
   nodelay(win, true);



   // snake moving mechanism
   int snakex= 0;  // snake head x-position
   int snakey= 0;  //snake head y-position
   int dirx=1;   // x-directiom
   int diry=0;    // y-direction
   int fruitx=rand(); // fruit x-position
   int fruity=rand(); //fruit y-position


  int h, w;         // height and width of terminal screen
  getmaxyx(stdscr, h, w);

   while(true) {
         int pressed= wgetch(win);
     
      if (pressed==KEY_LEFT){
         dirx=-1;
         diry=0;   }
       if (pressed==KEY_RIGHT){
         dirx=1;
         diry=0;   }
       if (pressed==KEY_UP){
         dirx=0;
         diry=-1;   }
       if (pressed==KEY_DOWN){
         dirx=0;
         diry=1;   }
      snakex+=dirx;
      snakey+=diry;
      erase();
      mvaddstr(snakey, snakex, "%");
      mvaddstr(fruity, fruitx, "@");
      usleep(200000);}
      endwin();









}











