#include "GameEngine.h"
#include <ncurses.h>
#include <unistd.h> // για το sleep
#include <ctime>
#include <iostream>
using namespace std;

//constructor gameEngine 
GameEngine::GameEngine(const string& filename)
    : labyrinth(filename),
      player('L', labyrinth.getMap()),
      autoPlayer('M', labyrinth.getMap()),
      prize('?', labyrinth.getMap()) {
    const vector<pair<int, int>>& freeSpaces = labyrinth.getFreeSpaces();
    
    //αρχικοποίηση θέσεων αντικειμένων
    //έλεγχος για να μην συμπίπτουν οι θέσεις
    player.initializePosition(freeSpaces);
    do {
        autoPlayer.initializePosition(freeSpaces);
    } while (autoPlayer.getPosX() == player.getPosX() && autoPlayer.getPosY() == player.getPosY());
    do {
        prize.initializePosition(freeSpaces);
    } while (goalFound());
}


//συνθήκη τερματισμού
bool GameEngine::goalFound() {
    if ((prize.getPosX() == player.getPosX() && prize.getPosY() == player.getPosY()) ||
        (prize.getPosX() == autoPlayer.getPosX() && prize.getPosY() == autoPlayer.getPosY())) {
        return true;
    }
    return false;
}


//αρχικοποιήση παιχνιδιού
void GameEngine::initializeGame() {
    lastPrizePlacement = time(0);
    initscr();    // Initialize ncurses
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_RED);
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);
    init_pair(4, COLOR_WHITE, COLOR_WHITE);
    noecho();
    keypad(stdscr, TRUE); //γτα ενεργοποιήση arrow keys
    curs_set(0);  // κρύβουμε τον κέρσορα

    labyrinth.print();
    player.print();
    autoPlayer.print();
    prize.print();
     mvprintw(labyrinth.getMap().size()+2, 4, "Welcome to the Wizard Games!\n");
    refresh();
}

//ανανέωση θέσεων αντικειμένων
void GameEngine::updateGame() {
    int key = getch();//input κίνησης user

    player.move(key);
    autoPlayer.moveTowardsPrize(prize);

    //διαλέγουμε τυχαία θέση για διαμάντι  
    time_t currentTime = time(nullptr);
    if (currentTime >= lastPrizePlacement +rand() % 11 + 5) { //range κάθε 5-15 seconds αλλαγή
        prize.clearPreviousPosition();  //καθαρισμός θέσης
        prize.initializePosition(labyrinth.getFreeSpaces()); //νέα θέση
        lastPrizePlacement = currentTime;
    }
    refresh();
    prize.print();
    autoPlayer.print();
    player.print();
    refresh();
}

//gameLoop
void GameEngine::playGame() {
    initializeGame();

    while (true) {
        if (goalFound()) {
            //αν φτάσουν μαζί
            if (autoPlayer.getPosX() == prize.getPosX() && autoPlayer.getPosY() == prize.getPosY() &&
                player.getPosX() == prize.getPosX() && player.getPosY() == prize.getPosY()) {
                attron(COLOR_PAIR(3)); 
                mvprintw(labyrinth.getMap().size()+4, 0, "It's a tie! You must fight...");
                attroff(COLOR_PAIR(3)); 
                //αν φτάσει ai-παιχτης
            } else if (autoPlayer.getPosX() == prize.getPosX() && autoPlayer.getPosY() == prize.getPosY()) {
                attron(COLOR_PAIR(2)); 
                mvprintw(labyrinth.getMap().size()+4, 0, "Congratulations, Mpampi Poteridi! 10 points to Gryffindor...");
                 attroff(COLOR_PAIR(2));
                 //αν φτάσει δικός μας παίχτης
            } else if (player.getPosX() == prize.getPosX() && player.getPosY() == prize.getPosY()) {
                attron(COLOR_PAIR(1)); 
                mvprintw(labyrinth.getMap().size()+4, 0, "Congratulations, Luca Malfoy! 10 points to Slytherin...");
                attroff(COLOR_PAIR(1));
            }
            break; // exit όταν βρεθεί το prize
        }

        updateGame();
    }

    refresh();
    getch(); // Περιμένουμε user input 
    sleep(2);
    endwin();  //Έξοδος ncurses
}
