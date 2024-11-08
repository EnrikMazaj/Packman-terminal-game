#include <ncurses.h>
#include "Player.h"
using namespace std;
 
Player::Player( char s, const vector<string>& m) : GameObject( s, m) {}
    
void Player::print() const {
        attron(COLOR_PAIR(1)); 
        mvaddch(posy, posx, symbol);
        attroff(COLOR_PAIR(1)); 
    }

bool Player::isValidMove(int x, int y) const {
        if (x < 0 || y < 0 || y >= map.size() || x >= map[y].size()) {
            return false;  // Out of bounds
        }
        return map[y][x] != '#';  // Not a wall
    }

void Player::move(int key) {
    int newX = posx; // νέα θέση x
    int newY = posy; // νέα θέση y
    bool validMove = false;

    do {
        switch (key) {
            case KEY_UP:
                newX = posx;
                newY = posy - 1;
                break;
            case KEY_DOWN:
                newX = posx;
                newY = posy + 1;
                break;
            case KEY_LEFT:
                newX = posx - 1;
                newY = posy;
                break;
            case KEY_RIGHT:
                newX = posx + 1;
                newY = posy;
                break;
            case ' ': // Handle spacebar
                return; // αγνόηση spacebar
            case 27: // Esc είσοδος
                endwin(); 
                exit(0); // Exit προγράμματος
            default:
                key = getch(); // σε οποιοδήποτε άλλη είσοδο περιμένουμε νέα 
                continue; 
        }

        if (isValidMove(newX, newY)) {
            mvaddch(posy, posx, '.'); //καθαρισμός θέσης
            posx = newX;
            posy = newY;
            mvaddch(posy, posx, symbol); // μετακίνηση σε νέα θέση και εκτύπωση χαρακτήρα
            validMove = true;
        } else {
            key = getch(); 
        }
    } while (!validMove); 
}
