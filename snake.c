
#include <stdio.h>  // standard input output library
#include <ncurses.h>// Library used for window creation, cursor movemen and keyboar input
#include <stdlib.h> // Library used for rand function 
#include <unistd.h> // Library used for usleep function

int main() {

WINDOW * win= initscr(); // initializes terminal screen
keypad(win, true); // allows for keyboard input
nodelay(win, true); // to make program continue running without waitinng for user input
curs_set(0);         // hides cursor

  
int max_y;  //window maximum width
int max_x;  // window maximum height
getmaxyx(stdscr, max_y, max_x);      // this function gets the maximum height and width of playing window


  
int snakeheadx=max_x/2;// snakehead starting coordinates
int snakeheady=max_y/2;
int directionx=1;// snake starting direction
int directiony=0;
int foodx=0;      // food starting coordinates
int foody=0;

while(true){       // playing mechanism
  
int pressed= wgetch(win);// gets user input from window
if (pressed== KEY_LEFT){   
  if (directionx== 1)  // prevents snake from turning 180 degrees
    continue;
directionx=-1;
directiony=0;
}
if(pressed== KEY_RIGHT){
   if (directionx== -1)  // prevents snake from turning 180 degrees
    continue;
  directionx=1;
directiony=0;}
if(pressed== KEY_DOWN){
   if (directiony== -1)  // prevents snake from turning 180 degrees
    continue;
  directionx=0;
directiony=1;}
if(pressed== KEY_UP){
   if (directiony== 1)  // prevents snake from turning 180 degrees
    continue;
  directionx=0;
directiony=-1;}

  snakeheadx+=directionx;
  snakeheady+=directiony;

  if(snakeheadx<0 || snakeheadx>max_x || snakeheady<0 || snakeheady>max_x)
{ erase();
  mvprintw(max_y/2, max_x/2, "Game Over!");}

erase();
mvaddstr(snakeheady, snakeheadx, "O");
mvaddstr(foody, foodx, "*");
usleep(200000);}


  
  

return 0;
}



