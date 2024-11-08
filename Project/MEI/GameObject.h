#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>
#include <string>

using namespace std;

class GameObject {
protected:
    int posx, posy;
    char symbol;
    const vector<string>& map;

public:
    //απλός constructor για χαρακτήρα και αντίγραφο χάρτη
    GameObject(char s, const std::vector<std::string>& m);

    virtual void print() const = 0;
    
    virtual ~GameObject() = default; //destructor

    void initializePosition(const vector<pair<int, int>>& freeSpaces); // για αρχική θέση 

    int getPosX() const;
    int getPosY() const;
};

#endif  // GAME_OBJECT_H
