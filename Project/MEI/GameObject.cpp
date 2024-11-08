#include "GameObject.h"
#include <cstdlib>
#include <ctime>
using namespace std;

GameObject::GameObject(char s, const vector<string>& m) : symbol(s), map(m) {}

void GameObject::initializePosition(const vector<pair<int, int>>& freeSpaces) {
    if (freeSpaces.empty()) {
        return;  //δεν υπάρχουν ελέυθερες θέσεις
    }

    // Διαλέγουμε τυχαία μία θέση με βάση πίνακα freespaces
    srand(time(nullptr));
    int selectedIndex = rand() % freeSpaces.size();
    const pair<int, int>& selectedSpace = freeSpaces[selectedIndex];

    //νέες συντεταγμένες
    posx = selectedSpace.first;
    posy = selectedSpace.second;
}

int GameObject::getPosX() const {
    return posx;
}

int GameObject::getPosY() const {
    return posy;
}
