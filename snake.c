
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
snakex[0] = 10 ;// snakehead starting coordinates
snakey[0] = 10;

int directionx=1;// snake starting direction
int directiony=0;
int foodx=rand() % max_x;  
if(foodx%2 != 0){
  foodx--;}// food starting coordinates
int foody=(rand() % (max_y-1))+1;
int score=0;    // score counter

// difficulty choosing mechanism
int choice;
int delay; //(usleep value that determines snake speed)
erase();
mvprintw((max_y/2)-4, max_x/2, "Select difficulty level:");
 mvprintw((max_y/2)-2, max_x/2, "1. Easy");
 mvprintw((max_y/2), max_x/2, "2. Medium");
  mvprintw((max_y/2)+2, max_x/2, "3. Hard");
  mvprintw((max_y/2)+4, max_x/2, "4. INSANE!");

  while(true){
    choice= wgetch(win);
    if(choice=='1' || choice=='2' || choice=='3' || choice=='4'){
      break;}}
    if(choice=='1'){
      delay=200000;}
    else if(choice=='2'){
      delay=150000;}
    else if(choice=='3'){
      delay=100000;}
    else if(choice=='4'){
      delay=40000;}
      
  
  

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

  snakex[0]+=directionx*2;  //to update snake position, multiplied by 2 to fix difference between verical and horizantal speed
  snakey[0]+=directiony;

  for(int i=1; i< snakelength; i++){                   // to detect self collision
    if(snakex[0]==snakex[i] && snakey[0]==snakey[i]){
      erase();
      mvprintw(max_y/2, max_x/2, "GAME OVER!");
      mvprintw((max_y/2)-2, max_x/2, "Final score: %d", score);
      usleep(10000000) // pause for 10 seconds
    return 0;}}
    

  if(snakex[0]==foodx && snakey[0]==foody){ // fruit spawning mechanism
    score+=10;
    if(snakelength < max_segments)  // increase the length of the snake and respwans the food 
    snakelength++;
    foodx=(rand() % max_x);
    if(foodx % 2 !=0){
      foodx++;}// to make sure food x-coordinate is even as the x-movement is in increments of two
    foody=(rand() % (max_y-1))+1;}    // to make sure food doesnt spawn on score row  

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
usleep(delay);}



  
  

return 0;
}



