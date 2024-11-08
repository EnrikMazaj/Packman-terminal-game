#ifndef PRIZE_H
#define PRIZE_H

#include <vector>
#include <string>
#include "GameObject.h"
using namespace std;

class Prize : public GameObject {
private:
  
public:
    Prize( char s, const vector<string>& m); //constructor
    ~Prize() = default; //destructor
    void print() const; // print object
    void clearPreviousPosition() const; //καθαρισμός της θέσης σε '.'

};


#endif // PRIZE_H