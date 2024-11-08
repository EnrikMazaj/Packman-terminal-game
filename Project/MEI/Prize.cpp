#include "Prize.h"
#include <ncurses.h>
using namespace std;

    Prize::Prize( char s, const vector<string>& m) : GameObject (s, m) {}
    void Prize::print() const {
        attron(COLOR_PAIR(3)); //κίτρινο χρώμα
        mvaddch(posy, posx, symbol);
        attroff(COLOR_PAIR(3)); // Reset 
    }

    void Prize::clearPreviousPosition() const {
        mvaddch(posy, posx, '.'); // καθαρισμός θέσης σε '.'
    }
