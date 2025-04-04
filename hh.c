#include <stdio.h>   // for standard input output functions
#include <ncurses.h>  // allows for window creation, cursor movement and keyboard input
#include <stdlib.h>  // used for rand function for fruit spawning
#include <unistd.h> // for usleep function used to delay program execution

int main() {

   initscr();     // terminal screen
   cbreak();               // Disable line buffering
    noecho();               // Don't echo key presses to the screen
    keypad(stdscr, TRUE);   // Enable special keys (e.g., arrow keys)

int h, w;         // height and width of terminal screen
getmaxyx(stdscr, h, w);

int nlines= 20 ; // vertical size of the screen
int ncols = 20;  // horizontal size of the screen
int x0= (w/2)-(0.5*ncols) ;       // x-coordinate of top left corner of the window set to center of terminal
int y0 = (h/2)-(0.5*nlines)  ;      // y-coordinate of top left corner of the window set to center of terminal

   if(nlines>=h) {    // height adjusted if snake box is taller than terminal
      nlines=h-4;
      ncols=h-4;
      }
   
   if(ncols>=w) {       //  width adjusted if snake box is wider than terminal
      ncols=w-4;
      nlines=w-4;
      }


   
WINDOW * win = newwin(nlines, ncols, y0, x0); // creating window
   refresh();
   

   // snake moving mechanism
   int snakex=0;  // snake head x-position
   int snakey=0;  //snake head y-position
   int dirx=1;   // x-directiom
   int diry=0;    // y-direction
   int fruitx=rand() % nlines; // fruit x-position
   int fruity=rand() % ncols; //fruit y-position
   int pressed= wgetch(win);
   while(true) {
      if (pressed==KEY_LEFT){
         dirx=-1;
         diry=0;   }
       if (pressed==KEY_RIGHT){
         dirx=1;
         diry=0;   }
       if (pressed==KEY_UP){
         dirx=0;
         diry=1;   }
       if (pressed==KEY_DOWN){
         dirx=0;
         diry=-1;   }
      snakex+=dirx;
      snakey+=diry;
      mvaddstr(snakex, snakey, "%");
      mvaddstr(fruitx, fruity, "@");
      usleep(200000);}
      endwin();
    return 0;
   
}

 




   




