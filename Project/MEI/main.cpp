#include <iostream>
#include "GameObject.h"
#include "Prize.h"
#include "Player.h"
#include "AutoPlayer.h"
#include "Labyrinth.h"
#include "GameEngine.h"


using namespace std;


int main(int argc, char* argv[]) {
    //έλεγχος για πέρασμα χάρτη σαν όρισμα
     if (argc < 2) {
        cout << "Please write the map you want to play." << endl;
        return 1;
    }
    GameEngine game(argv[1]);
    game.playGame();

    return 0;
}
