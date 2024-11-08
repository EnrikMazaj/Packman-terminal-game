#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <string>
#include "Labyrinth.h"
#include "Player.h"
#include "AutoPlayer.h"
#include "Prize.h"

class GameEngine {
private:
    Labyrinth labyrinth;
    Player player;
    AutoPlayer autoPlayer;
    Prize prize;
    time_t lastPrizePlacement;

public:
    GameEngine(const std::string& filename);
    //έλεγχος συνθήκης τερματισμού
    bool goalFound();

    //αρχικοποιήση παιχνιδιού
    void initializeGame();
    
    //ανανέωση θέσεων αντικειμένων
    void updateGame();
    
    //gameloop
    void playGame();
};

#endif  // GAME_ENGINE_H
