#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
using namespace std;

struct Character {
    public:
        string name;
        int strength;
        int intelligence;
        int charisma;

        int health;
        int morale;
        int fatigue;
        int loyalty;
        
        string roles;
};

#endif