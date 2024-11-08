#ifndef PLAYER_H
#define PLAYER_H

using namespace std;
#include <vector>
#include "GameObject.h"


class Player : public GameObject {
public:

    Player( char s, const vector<string>& m);//constructor
    ~Player() = default; //destructor
    void print() const; //print αντικειμένου
    bool isValidMove(int x, int y) const; //έλεγχος για τοίχο η εκτός οριών
    void move(int key); //κίνηση παίχτη
};

#endif 