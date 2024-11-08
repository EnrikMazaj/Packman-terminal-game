#include "Labyrinth.h"
#include <ncurses.h>
#include <fstream>
using namespace std;

Labyrinth::Labyrinth(const string& filename) {
    readFromFile(filename);
}

//euresh kenwn thesewn '.'
vector<pair<int, int>> Labyrinth::getFreeSpaces() const {
    vector<pair<int, int>> freeSpaces;

    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
            if (map[y][x] == '.') {
                freeSpaces.emplace_back(x, y);  //apothikeysh se vector freespaces
            }
        }
    }

    return freeSpaces;
}


//diabasma arxiou
void Labyrinth::readFromFile(const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        map.push_back(line);
    }
    file.close();
}

void  Labyrinth::print() const {
    for (const auto& row : map) {
        for (const char& cell : row) {
            if (cell == '#') {
                attron(COLOR_PAIR(4)); //Μετατροπή τοίχου σε white block
                addch(' '); // Print  white block
                attroff(COLOR_PAIR(4)); // Επαναφορά
            } else {
                printw("%c", cell); //Παραμένουν τα '.' ώς έχουν
            }
        }
        printw("\n");
    }
}

const vector<string>& Labyrinth::getMap() const {
    return map;
}
