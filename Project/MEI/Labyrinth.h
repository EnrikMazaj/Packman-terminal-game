#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <string>
#include <vector>
using namespace std;

class Labyrinth {
private:
    vector<string> map;

public:
    Labyrinth(const string& filename);

    //vector για εύρεση κενών θέσεων
    vector<pair<int, int>> getFreeSpaces() const;

    void readFromFile(const string& filename); //διάβασμα αρχείου

    void print() const; //print map

    const vector<string>& getMap() const;
};

#endif // LABYRINTH_H
