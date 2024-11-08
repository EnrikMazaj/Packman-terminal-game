#include "AutoPlayer.h"
#include <ncurses.h>
#include <queue>
using namespace std;

AutoPlayer::AutoPlayer(char s, const vector<string>& m) : GameObject(s, m) {}

void AutoPlayer::print() const {
    attron(COLOR_PAIR(2)); // ορισμός κόκκινου χρώματος
    mvaddch(posy, posx, symbol);
    attroff(COLOR_PAIR(2)); // επαναφορά
}

void AutoPlayer::moveTowardsPrize(const Prize& prize) {
    int prizeX = prize.getPosX();
    int prizeY = prize.getPosY();
    int rows = map.size();
    int columns = map[0].size();

    // 2D πίνακας για τις αποστάσεις κάθε κελιού από την θέση του AI παίκτη
    vector<vector<int>> distanceCells(rows, vector<int>(columns, -1));
    // 2D πίνακας για να αποθηκεύει τις προηγούμενες θέσεις για κάθε κελί
    vector<vector<pair<int, int>>> visitedCells(rows, vector<pair<int, int>>(columns, make_pair(-1, -1)));
    // ουρά για τον αλγόριθμο BFS
    queue<pair<int, int>> q;

    // αρχικοποίηση
    q.push(make_pair(posx, posy)); //αρχική θέση μπαίνει στην ουρά
    distanceCells[posy][posx] = 0;   //Η απόσταση γίνεται 0

   
    // Έναρξη BFS
    while (!q.empty()) { //έλεγχος κενής ουράς
        pair<int, int> position = q.front();  
        q.pop();    //βγάζουμε το πρώτο ζευγάρι

        int x = position.first;
        int y = position.second;

    //ελεγχος αν είμαστε στην θέση του prize
        if (x == prizeX && y == prizeY) { 
            break;
        }

         // έλεγχος των γειτονικών θέσεων: πάνω, κάτω, αριστερά, δεξιά
        vector<pair<int, int>> neighborsCells = {{x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}};
        for (const auto& neighbor : neighborsCells) {
            int newX = neighbor.first;
            int newY = neighbor.second;

             // χρήση της isValidMove για έλεγχο τοίχου ή εκτός ορίων
            if (isValidMove(newX, newY) && distanceCells[newY][newX] == -1) {
                mvaddch(posy, posx, '.');   //καθαρισμός θέσης
                q.push(neighbor);       //νέα θέση για έλεγχο
                distanceCells[newY][newX] = distanceCells[y][x] + 1;  // ενημέρωση αποστάσεων
                visitedCells[newY][newX] = position;  // ορισμός προηγούμενης θέσης
            }
        }
    }

    // φτιάχνουμε το μονοπάτι από τη θέση προς το prize
    vector<pair<int, int>> path;
    int x = prizeX;
    int y = prizeY;
    while (x != posx || y != posy) {
        path.push_back(make_pair(x, y));
        pair<int, int> visited = visitedCells[y][x];
        x = visited.first;
        y = visited.second;
    }

    //εκτέλεση βήματος
    if (!path.empty()) {
        pair<int, int> nextMove = path.back();
        int nextX = nextMove.first;
        int nextY = nextMove.second;
        posx = nextX;
        posy = nextY;
    }
}

//έλεγχος για την κίνηση του παίχτη τοίχος η εκτός οριών
bool AutoPlayer::isValidMove(int x, int y) const {
    if (x < 0 || y < 0 || y >= map.size() || x >= map[y].size()) {
        return false;  // εκτός οριών
    }
    return map[y][x] != '#';  // Αν δεν είναι τοίχος
}
