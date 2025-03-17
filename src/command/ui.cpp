/*----------------------------------------------------------------------*
 *                           USER INTERFACE                             *
 *----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------

    Builds a Graphical CLI UI with PDCurses

------------------------------------------------------------------------*/

#include "../inc/command/ui.h"
#include <curses.h>
#include <string>
#include "utils/logger.h"

using namespace std;

// Window dimensions and positions
struct UILayout {
    int screen_height;
    int screen_width;
    int sidebar_width;
    int content_width;
    int header_height;
};

void draw_header(WINDOW* win, int width) {
    wattron(win, COLOR_PAIR(1) | A_BOLD);
    mvwprintw(win, 1, width/2 - 13, "Krypton Version Control");
    mvwprintw(win, 2, width/2 - 8, "Version 1.0");
    wattroff(win, COLOR_PAIR(1) | A_BOLD);
    wrefresh(win);
}

void draw_sidebar(WINDOW* win) {
    box(win, 0, 0);
    wattron(win, COLOR_PAIR(2) | A_BOLD);
    mvwprintw(win, 1, 2, "NAVIGATION");
    wattroff(win, COLOR_PAIR(2) | A_BOLD);
    
    // Menu items
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, 3, 2, "1. Status");
    mvwprintw(win, 4, 2, "2. Stage");
    mvwprintw(win, 5, 2, "3. Commit");
    mvwprintw(win, 6, 2, "4. Branch");
    mvwprintw(win, 7, 2, "5. Remote");
    mvwprintw(win, 9, 2, "q. Quit");
    wattroff(win, COLOR_PAIR(2));
    
    wrefresh(win);
}

void draw_content(WINDOW* win) {
    box(win, 0, 0);
    wattron(win, COLOR_PAIR(3) | A_BOLD);
    mvwprintw(win, 1, 2, "WORKSPACE");
    wattroff(win, COLOR_PAIR(3) | A_BOLD);
    
    wattron(win, COLOR_PAIR(3));
    mvwprintw(win, 3, 2, "Current Branch: main");
    mvwprintw(win, 4, 2, "Status: Ready");
    wattroff(win, COLOR_PAIR(3));
    
    wrefresh(win);
}

void krypton_ui()
{
    // Initialize curses
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);  // Hide cursor

    // Set up colors
    init_pair(1, COLOR_GREEN, COLOR_BLACK);   // Header
    init_pair(2, COLOR_CYAN, COLOR_BLACK);    // Sidebar
    init_pair(3, COLOR_WHITE, COLOR_BLACK);   // Content

    // Get screen dimensions
    UILayout layout;
    getmaxyx(stdscr, layout.screen_height, layout.screen_width);
    layout.sidebar_width = layout.screen_width / 4;
    layout.content_width = layout.screen_width - layout.sidebar_width;
    layout.header_height = 4;

    // Create windows
    WINDOW* header = newwin(layout.header_height, layout.screen_width, 0, 0);
    WINDOW* sidebar = newwin(layout.screen_height - layout.header_height, 
                           layout.sidebar_width, layout.header_height, 0);
    WINDOW* content = newwin(layout.screen_height - layout.header_height,
                           layout.content_width, layout.header_height, layout.sidebar_width);

    // Draw initial layout
    draw_header(header, layout.screen_width);
    draw_sidebar(sidebar);
    draw_content(content);

    // Main event loop
    int ch;
    while ((ch = getch()) != 'q' && ch != 'Q')
    {
        switch(ch) {
            case '1':
                // Handle Status
                wclear(content);
                box(content, 0, 0);
                mvwprintw(content, 1, 2, "Status View");
                wrefresh(content);
                break;
            case '2':
                // Handle Stage
                wclear(content);
                box(content, 0, 0);
                mvwprintw(content, 1, 2, "Stage View");
                wrefresh(content);
                break;
            case '3':
                // Handle Commit
                wclear(content);
                box(content, 0, 0);
                mvwprintw(content, 1, 2, "Commit View");
                wrefresh(content);
                break;
            case '4':
                // Handle Branch
                wclear(content);
                box(content, 0, 0);
                mvwprintw(content, 1, 2, "Branch View");
                wrefresh(content);
                break;
            case '5':
                // Handle Remote
                wclear(content);
                box(content, 0, 0);
                mvwprintw(content, 1, 2, "Remote View");
                wrefresh(content);
                break;
        }
    }

    // Clean up
    delwin(header);
    delwin(sidebar);
    delwin(content);
    endwin();
}