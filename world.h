#ifndef WORLD_H
#define WORLD_H

#include <string>
using namespace std;

struct World {
    public:
        string name;

        char terrain;           // 'P', 'M', etc.
        int elevation;          // 0-100
        float resrouces;        //0.0-1.0
        bool isRadiated;        // true or false
        bool hasAlienRuins;

        string type;            // Icy
        string atmosphere;      // Toxic
        float gravity;          // 0.8 = low gravity
        float avgTemperature;    // In Celsius
        int dayLength;          // in minutes
        int radiationLevel;      // 0-3 scale
};

#endif