#ifndef AUTOPLAYER_H
#define AUTOPLAYER_H

#include <vector>
#include <string>
#include "GameObject.h"
#include "Prize.h"

class AutoPlayer : public GameObject {
public:
    AutoPlayer(char s, const std::vector<std::string>& m);

    void print() const override; //override μεθόδου εκτύπωσης gameObject
    void moveTowardsPrize(const Prize& prize); //bfs αλγόριθμος κίνησης ai-player

private:
    bool isValidMove(int x, int y) const; //έλεγχος κίνησης
};

#endif