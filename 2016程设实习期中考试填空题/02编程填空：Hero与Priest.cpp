#include <iostream>
using namespace std;
class Hero {
public:
    void attack() { cout << "Hero::attack()" << endl; }
    virtual void defense() { cout << "Hero::defense()" << endl; } 
};
class Priest: public Hero {
public:
    virtual void attack() { cout << "Priest::attack()" << endl; }
    virtual void defense() { cout << "Priest::defense()" << endl; } 
}; 

int main() {
    Priest anduin;
    Hero h;
    h.defense();
    Hero *player = &anduin;
    player->attack();
    player->defense();
    anduin.attack();
    anduin.defense();
    return 0;
}
