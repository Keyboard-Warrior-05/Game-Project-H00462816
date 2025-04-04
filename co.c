#include <stdio.h>   // for standard input output functions
#include <ncurses.h>  // allows for window creation, cursor movement and keyboard input
#include <stdlib.h>  // used for rand function for fruit spawning
#include <unistd.h> // for usleep function used to delay program execution

void setupWindow(int *nlines, int *ncols, int *x0, int *y0);
void gameLoop(WINDOW *win, int nlines, int ncols);

int main() {
    initscr();  // Initialize the screen
    cbreak();
    noecho();
    keypad(stdscr, TRUE);  // Enable special keys for the entire screen

    int nlines = 20, ncols = 40, x0, y0;
    setupWindow(&nlines, &ncols, &x0, &y0);

    WINDOW *win = newwin(nlines, ncols, y0, x0);
    if (win == NULL) {
        fprintf(stderr, "Error creating window.\n");
        endwin();
        exit(EXIT_FAILURE);
    }
    keypad(win, TRUE);  // Enable special keys for the specific window

    box(win, 0, 0);  // Draw a box around the window
    wrefresh(win);   // Refresh the window to show the box

    // Use mvprintw to print to the standard screen
    mvprintw(0, 0, "Window size: %d x %d", nlines, ncols);
    mvprintw(1, 0, "Window position: (%d, %d)", x0, y0);
    refresh();  // Refresh to show the printed text

    gameLoop(win, nlines, ncols);

    endwin();
    return 0;
}

void setupWindow(int *nlines, int *ncols, int *x0, int *y0) {
    int h, w;
    getmaxyx(stdscr, h, w);

    *x0 = (w / 2) - (0.5 * (*ncols));
    *y0 = (h / 2) - (0.5 * (*nlines));

    if (*nlines >= h) {
        *nlines = h - 4;
        *ncols = h - 4;
    }
    if (*ncols >= w) {
        *ncols = w - 4;
        *nlines = w - 4;
    }
}

void gameLoop(WINDOW *win, int nlines, int ncols) {
    int snakex = nlines / 2, snakey = ncols / 2;
    int dirx = 1, diry = 0;
    int fruitx = rand() % nlines;
    int fruity = rand() % ncols;

    while (true) {
        werase(win);
        box(win, 0, 0);  // Redraw the box around the window
        mvwprintw(win, snakex, snakey, "%c", '%');
        mvwprintw(win, fruitx, fruity, "%c", '@');
        wrefresh(win);
        usleep(200000);

        int pressed = wgetch(win);
        if (pressed == 'q') break;  // Exit the game loop if 'q' is pressed
        if (pressed == KEY_LEFT) { dirx = -1; diry = 0; }
        if (pressed == KEY_RIGHT) { dirx = 1; diry = 0; }
        if (pressed == KEY_UP) { dirx = 0; diry = -1; }
        if (pressed == KEY_DOWN) { dirx = 0; diry = 1; }

        // Update snake position
        snakex += dirx;
        snakey += diry;

        // Use mvprintw to print snake position to the standard screen
        mvprintw(2, 0, "Snake position: (%d, %d)", snakex, snakey);
        refresh();  // Refresh to show the printed text

        // Ensure the snake stays within the window boundaries
        if (snakex < 0) snakex = 0;
        if (snakex >= nlines) snakex = nlines - 1;
        if (snakey < 0) snakey = 0;
        if (snakey >= ncols) snakey = ncols - 1;

        // Check if snake eats the fruit
        if (snakex == fruitx && snakey == fruity) {
            fruitx = rand() % nlines;
            fruity = rand() % ncols;
        }
    }
}
