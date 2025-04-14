
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


int max_segments= (max_x*max_y)-1;  // calculates maximum snake size based on screen size
int snakex[max_segments];           // x-coordinate of snake segments
int snakey[max_segments];           // y-coordinate of snake segments
int snakelength=1;                  // initial snake length
snakex[0] = max_x/2;// snakehead starting coordinates
snakey[0] = max_y/2;

int directionx=1;// snake starting direction
int directiony=0;
int foodx=0;      // food starting coordinates
int foody=0;
int score=0;    // score counter

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

  for(int i= snakelength-1; i>0;  i--){
    snakex[i]=snakex[i-1];
    snakey[i]=snakey[i-1];  }

  snakex[0]+=directionx;
  snakey[0]+=directiony;

  if(snakex[0]==foodx && snakey[0]==foody){ // fruit spawning mechanism
    score+=10;
    if(snakelength < max_segments)  // increase the length of the snake and respwans the food 
    snakelength++;
    foodx=rand() % max_x;
    foody=(rand() % max_y)+1;}

  if(snakex[0]<0){           // snake wrapping logic
    snakex[0]=max_x;}
  if(snakex[0]>max_x){
    snakex[0]=0; }
  
   if(snakey[0]<1){
    snakey[0]=max_y;}
  if(snakey[0]>max_y){
    snakey[0]=1; }

  
erase();

  mvprintw(0, max_x/2, "score: %d", score); // score counter
    
  for(int i = 0; i < snakelength; i++){
    mvaddstr(snakey[i], snakex[i], "O");}
mvaddstr(foody, foodx, "#");

  //to fix difference between verical and horizantal speed
  if(directionx=1){
    usleep(100000);}
  else{
usleep(200000);}}

  


  
  

return 0;
}



