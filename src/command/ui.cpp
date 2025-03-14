/*----------------------------------------------------------------------*
 *                           USER INTERFACE                             *
 *----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------

    Builds a Graphical CLI UI with PDCurses

------------------------------------------------------------------------*/

#include "../inc/command/ui.h"
#include <curses.h>

void krypton_ui()
{
    initscr();
    noecho();
    curs_set(0);
    refresh();  // Ensure screen updates before creating windows

    int screen_height, screen_width;
    getmaxyx(stdscr, screen_height, screen_width);  // Get terminal size

    int sidebar_width = screen_width / 4;  // Sidebar takes 1/4 of screen
    int content_width = screen_width - sidebar_width;  // Remaining space

    // Create sidebar (left) and content area (right)
    WINDOW *sidebar = newwin(screen_height, sidebar_width, 0, 0);
    WINDOW *content = newwin(screen_height, content_width, 0, sidebar_width);

    // Draw borders
    box(sidebar, 0, 0);
    box(content, 0, 0);

    // Add labels
    mvwprintw(sidebar, 1, 1, "Sidebar");
    mvwprintw(content, 1, 1, "Content Area");

    // Refresh both windows
    wrefresh(sidebar);
    wrefresh(content);

    getch();  // Wait for key press
    endwin(); // Restore terminal
}