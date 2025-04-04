#include <stdio.h>   // for standard input output functions
#include <ncurses.h>  // allows for window creation, cursor movement and keyboard input
#include <stdlib.h>  // used for rand function for fruit spawning
#include <unistd.h> // for usleep function used to delay program execution

int main() {

   initscr();     // terminal screen
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
   
box(win, 105, 105);                           // creating play box
   wrefresh(win);

    int ch;
    while ((ch = getch()) != 'q') { // Wait for 'q' key to exit
        // Handle special keys (e.g., arrow keys)
        switch (ch) {
            case KEY_UP:
                mvwprintw(win, 1, 1, "Up key pressed   ");
                break;
            case KEY_DOWN:
                mvwprintw(win, 2, 1, "Down key pressed ");
                break;
            case KEY_LEFT:
                mvwprintw(win, 3, 1, "Left key pressed ");
                break;
            case KEY_RIGHT:
                mvwprintw(win, 4, 1, "Right key pressed");
                break;
            default:
                mvwprintw(win, 5, 1, "Key pressed: %c  ", ch);
                break;
        }
        wrefresh(win);
    }
    delwin(win);              // Delete the window
    endwin();                 // Restore terminal settings

    return 0;
}

 




   



}
