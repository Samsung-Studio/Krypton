/*----------------------------------------------------------------------*
 *                           USER INTERFACE                             *
 *----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------

    Builds a Graphical CLI UI with PDCurses

------------------------------------------------------------------------*/

#include "../inc/command/ui.h"
#include <curses.h>
#include <string>
#include <cstring>
#include "utils/logger.h"

using namespace std;

// Window dimensions and positions
struct UILayout
{
    int screen_height;
    int screen_width;
    int sidebar_width;
    int content_width;
    int header_height;
};

// UI state
struct UIState
{
    int selected_menu;
    bool menu_active;
};

void draw_header(WINDOW* win, int width)
{
    // Remove box(win, 0, 0) to eliminate the border
    wattron(win, COLOR_PAIR(1) | A_BOLD);
    mvwprintw(win, 1, (width - 20) / 2, "Krypton Version Control");
    mvwprintw(win, 2, (width - 10) / 2, "Version 1.0");
    wattroff(win, COLOR_PAIR(1) | A_BOLD);
    wrefresh(win);
}

void draw_menu_item(WINDOW* win, int y, int selected, const char* text, int number)
{
    int width = getmaxx(win) - 2; // Account for borders
    
    if (selected)
    {
        wattron(win, COLOR_PAIR(4) | A_BOLD);  // Removed A_REVERSE
        // Fill entire line with highlight
        mvwhline(win, y, 1, ' ', width);
        mvwprintw(win, y, 2, "%d", number);
        mvwprintw(win, y, 4, "%s", text);
        wattroff(win, COLOR_PAIR(4) | A_BOLD);  // Removed A_REVERSE
    }
    else
    {
        wattron(win, COLOR_PAIR(2));
        mvwprintw(win, y, 2, "%d", number);
        mvwprintw(win, y, 4, "%s", text);
        wattroff(win, COLOR_PAIR(2));
    }
}

void draw_sidebar(WINDOW* win, const UIState& state)
{
    // Clear window and draw border
    werase(win);
    box(win, 0, 0);
    
    // Draw title
    wattron(win, COLOR_PAIR(2) | A_BOLD);
    mvwprintw(win, 1, (getmaxx(win) - 10) / 2, "NAVIGATION");
    wattroff(win, COLOR_PAIR(2) | A_BOLD);
    
    // Draw menu items
    const char* menu_items[] = {"Status", "Stage", "Commit", "Branch", "Remote"};
    for (int i = 0; i < 5; i++)
    {
        draw_menu_item(win, i + 3, i == state.selected_menu, menu_items[i], i + 1);
    }
    
    // Draw quit option
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, 9, 2, "q");
    mvwprintw(win, 9, 4, "Quit");
    wattroff(win, COLOR_PAIR(2));
    
    wrefresh(win);
}

void draw_content_title(WINDOW* win, const char* title)
{
    int width = getmaxx(win) - 2;
    wattron(win, COLOR_PAIR(3) | A_BOLD);
    mvwhline(win, 1, 1, ' ', width);
    mvwprintw(win, 1, (width - strlen(title)) / 2 + 1, "%s", title);
    wattroff(win, COLOR_PAIR(3) | A_BOLD);
}

void draw_content(WINDOW* win, const UIState& state)
{
    // Clear window and draw border
    werase(win);
    box(win, 0, 0);
    
    const char* titles[] =
    {
        "REPOSITORY STATUS",
        "STAGING AREA",
        "COMMIT CHANGES",
        "BRANCH MANAGEMENT",
        "REMOTE REPOSITORIES"
    };
    
    draw_content_title(win, titles[state.selected_menu]);
    
    // Draw separator line
    wattron(win, COLOR_PAIR(3));
    mvwhline(win, 2, 1, ACS_HLINE, getmaxx(win) - 2);
    wattroff(win, COLOR_PAIR(3));
    
    wattron(win, COLOR_PAIR(3));
    switch(state.selected_menu)
    {
        case 0:
            mvwprintw(win, 4, 2, "Current Branch : main");
            mvwprintw(win, 5, 2, "Status : Ready");
            break;
        case 1:
            mvwprintw(win, 4, 2, "No files staged for commit !");
            break;
        case 2:
            mvwprintw(win, 4, 2, "No changes to commit !");
            mvwprintw(win, 5, 2, "Use number keys (1-5) to navigate");
            mvwprintw(win, 6, 2, "Press Enter to select an option");
            break;
        case 3:
            mvwprintw(win, 4, 2, "Current Branch : main");
            mvwprintw(win, 5, 2, "No other branches available !");
            break;
        case 4:
            mvwprintw(win, 4, 2, "No remote repositories configured");
            mvwprintw(win, 5, 2, "Use 'remote add' to configure a remote");
            break;
    }
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
    refresh();

    // Set up colors
    init_pair(1, COLOR_GREEN, COLOR_BLACK);   // Header
    init_pair(2, COLOR_WHITE, COLOR_BLACK);   // Sidebar
    init_pair(3, COLOR_WHITE, COLOR_BLACK);   // Content
    init_pair(4, COLOR_BLACK, COLOR_WHITE);   // Selected menu item

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

    // Initialize UI state
    UIState state;
    state.selected_menu = 0;
    state.menu_active = true;

    // Draw initial layout
    draw_header(header, layout.screen_width);
    draw_sidebar(sidebar, state);
    draw_content(content, state);

    // Main event loop
    int ch;
    while ((ch = getch()) != 'q' && ch != 'Q')
    {
        if (state.menu_active)
        {
            switch(ch)
            {
                case KEY_UP:
                    if (state.selected_menu > 0)
                    {
                        state.selected_menu--;
                        draw_sidebar(sidebar, state);
                        draw_content(content, state);
                    }
                    break;
                case KEY_DOWN:
                    if (state.selected_menu < 4)
                    {
                        state.selected_menu++;
                        draw_sidebar(sidebar, state);
                        draw_content(content, state);
                    }
                    break;
                case KEY_ENTER:
                case 10: // Enter key
                    state.menu_active = false;
                    draw_sidebar(sidebar, state);
                    draw_content(content, state);
                    break;
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                    state.selected_menu = ch - '1';
                    state.menu_active = false;
                    draw_sidebar(sidebar, state);
                    draw_content(content, state);
                    break;
            }
        }
        else
        {
            switch(ch)
            {
                case KEY_LEFT:
                    state.menu_active = true;
                    draw_sidebar(sidebar, state);
                    draw_content(content, state);
                    break;
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                    state.selected_menu = ch - '1';
                    draw_sidebar(sidebar, state);
                    draw_content(content, state);
                    break;
            }
        }
    }

    // Clean up
    delwin(header);
    delwin(sidebar);
    delwin(content);
    endwin();
}