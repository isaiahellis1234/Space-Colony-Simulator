#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

// # HEADERS
#include "character.h"
#include "inventory.h"
#include "functions.h"
#include "world.h"

// # OTHER
#include <string>
#include <ctime>
#include <random>
#include <limits>
#include <cstdlib>

#include "windows.h"
#include <iostream>
using namespace std;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// # 5 characters to control

void start();
void stats();
void inventory_stats();

float getSmoothNoise(int x, int y, unsigned int seed);
char getTerrain(float noise);
string getRandomFromList(const string options[], int size, unsigned int seed);
World generateWorldMeta(unsigned int seed);
void generateTerrain(unsigned int seed);
void printWorldMap();
void printWorldMeta(const World& w);
// void worldGen();

string story = "After centuries of silent drift through the void, the colony ship finally arrived at its destination — a pale-blue world nestled in the arms of a distant star. Its hull was scarred from micrometeorites, and its systems aged but intact. The cryopods began to hiss open one by one, releasing descendants of a long-forgotten Earth into the light of a new sun. This was not a landing—it was a rebirth.";

Character characters[5];
Inventory inventory;



int main() {
    unsigned int seed;

    srand(time(NULL));
    start();
    
    system("cls");
    
    cout << "This is the story..." << endl;
    cout << story << endl;
    
    stats();
    inventory_stats();
    
    system("Pause");
    system("cls");
    cout << "Enter seed: ";
    cin >> seed;
    World myWorld = generateWorldMeta(seed);
    generateTerrain(seed);

    printWorldMeta(myWorld);
    printWorldMap();
    system("Pause");
    system("cls");
    cout << "*****************************************************************" << endl;
    cout << "\n";
    setColor(6);
    cout << "****************** SPACE COLONY SIMULATOR ***********************" << endl;
    setColor(0);
    cout << "\n";
    cout << "*****************************************************************" << endl;
    cout << "After a long journey through deep space,\nthe colony ship Auroras Hope veered off course during its final descent,\npulled in by the unexpected gravity of an uncharted planet.\nSystems failed one by one—navigation,\ncomms,\nengines,\nuntil the ship plummeted through the dense atmosphere, fire trailing from its hull.\nThe crash was violent, scattering debris across a jagged alien landscape.\nMiraculously, five survivors emerged from the wreckage,\nbruised but alive, surrounded by a strange and hostile world.\nWith no way to contact Earth and dwindling supplies,\nthey knew one thing for certain: this planet\nwas their new home—whether they were ready or not." << endl;
    system("Pause");
    return 0;
}

void stats() {
    int randomStats;
    int stats_input;
    int character_stats;
    cout << "Time to name the team" << endl;
    cout << " *********** NAMING **************" << endl;
    for (int i = 1; i <= 5; i++) {
        switch (i) {
            case 1:
                cout << "Name Leader: ";
                break;
            case 2:
                cout << "Name Medic: ";
                break;
            case 3:
                cout << "Name Engineer: ";
                break;
            case 4:
                cout << "Name Scout: ";
                break;
            case 5:
                cout << "Name Scientist: ";
        }
        cin >> characters[i - 1].name;
    }
    characters[0].roles = "Leader";
    characters[1].roles = "Medic";
    characters[2].roles = "Engineer";
    characters[3].roles = "Scout";
    characters[4].roles = "Scientist";
    // for (Character character : characters) {
    //     cout << "Characters: " << character.name << endl;
    // }

    cout << "Time to make the stats" << endl;
    cout << "1 - Create Stats" << endl;
    cout << "2 - Randomize Stats" << endl;
    // cin >> stats_input;
    stats_input = getValidNumber();

    switch (stats_input) {
        case 1:
            for (int i = 0; i < sizeof(characters)/sizeof(characters[0]); i++) {
                system("cls");
                cout << "Please enter the strength for: " << characters[i].name << endl;
                cin >> stats_input;
                if (stats_input > 10) {
                    characters[i].strength = 10;
                }
                else if (stats_input < 1) {
                    characters[i].strength = 1;
                }
                else {
                    characters[i].strength = stats_input;
                }
                cout << "Please enter the intelligence for: " << characters[i].name << endl;
                cin >> stats_input;
                if (stats_input > 10) {
                    characters[i].intelligence = 10;
                }
                else if (stats_input < 1) {
                    characters[i].intelligence = 1;
                }
                else {
                    characters[i].intelligence = stats_input;
                }
                cout << "Please enter the charisma for: " << characters[i].name << endl;
                cin >> stats_input;
                if (stats_input > 10) {
                    characters[i].charisma = 10;
                }
                else if (stats_input < 1) {
                    characters[i].charisma = 1;
                }
                else {
                    characters[i].charisma = stats_input;
                }
            }
            break;
        case 2:
            for (int i = 0; i < sizeof(characters)/sizeof(characters[0]); i++) {
                // Strength
                randomStats = rand() % 10 + 1;
                characters[i].strength = randomStats;

                // Intelligence
                randomStats = rand() % 10 + 1;
                characters[i].intelligence = randomStats; 

                // Charisma
                randomStats = rand() % 10 + 1;
                characters[i].charisma = randomStats;
            }
            break;
    }
    do {
        // for (int i = 0; i < sizeof(characters)/sizeof(characters[0]); i++) {
        //     cout << "Please enter Strength (1-10): ";
        //     cin >> 
        // }
        cout << "1 - See stats" << endl;
        cout << "2 - Finished with stats" << endl;
        cin >> stats_input;
        switch (stats_input) {
            case 1:
                cout << "which character (1-5): ";
                cin >> character_stats;
                if (character_stats <= 5 && character_stats > 0) {
                    cout << "Name: " << characters[character_stats].name << endl;
                    cout << "Stength: " << characters[character_stats].strength << endl;
                    cout << "Intelligence: " << characters[character_stats].intelligence << endl;
                    cout << "Charisma: " << characters[character_stats].charisma << endl;
                } else {
                    cout << "Not a character" << endl;
                }
                break;
            case 2:
                break;
            default:
                cout << "Invalid Input" << endl;
        }

    } while (stats_input != 2);
}

void inventory_stats() {
    int input;
    int choice;
    int quantity;

    do {
        cout << "This is where you buy inventory?: " << endl;
        cout << "1 - Meat + Fish" << endl;
        cout << "2 - Grain" << endl;
        cout << "3 - Fruit" << endl;
        cout << "4 - Dairy Products" << endl;
        cout << "5 - Processed + Cooked Food" << endl;
        cout << "6 - Drinks" << endl;
        cout << "7 - See Inventory" << endl;
        cout << "8 - Finish Inventory" << endl;
        cin >> input;
        if (cin.fail()) {
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number.\n";
            system("pause");
            continue;
        }

        switch (input) {
            case 1:
                cout << "1 - Cow" << endl;
                cout << "2 - Pig" << endl;
                cout << "3 - Chicken" << endl;
                cin >> choice;
                switch (choice) {
                    case 1:
                        cout << "How many?: ";
                        cin >> quantity;
                        inventory.cow += quantity;
                        break;
                    case 2:
                        cout << "How many?: ";
                        cin >> quantity;
                        inventory.pig += quantity;
                        break;
                    case 3:
                        cout << "How many?: ";
                        cin >> quantity;
                        inventory.chicken += quantity;
                        break;
                    default:
                        cout << "Invalid Input!" << endl;
                        break;
                }
                break;
            case 2:
                cout << "1 - Corn" << endl;
                cout << "2 - Rice" << endl;
                cout << "3 - Wild Rice" << endl;
                cout << "4 - Oats" << endl;
                cin >> choice;
                switch (choice) {
                    case 1:
                        cout << "How many?: ";
                        cin >> quantity;
                        inventory.corn += quantity;
                        break;
                    case 2:
                        cout << "How many?: ";
                        cin >> quantity;
                        inventory.rice += quantity;
                        break;
                    case 3:
                        cout << "How many?: ";
                        cin >> quantity;
                        inventory.wild_rice += quantity;
                        break;
                    case 4:
                        cout << "How many?: ";
                        inventory.oats += quantity;
                    default:
                        cout << "Invalid Input!" << endl;
                        break;
                }
                break;
            case 3:
                cout << "1 - Strawberries" << endl;
                cout << "2 - Apples" << endl;
                cout << "3 - Peaches" << endl;
                cin >> choice;
                switch (choice) {
                    case 1:
                        cout << "How many?: ";
                        cin >> quantity;
                        inventory.strawberries += quantity;
                        break;
                    case 2:
                        cout << "How many?: ";
                        cin >> quantity;
                        inventory.apples += quantity;
                        break;
                    case 3:
                        cout << "How many?: ";
                        cin >> quantity;
                        inventory.peaches += quantity;
                        break;
                    default:
                        cout << "Invalid Input!" << endl;
                        break;
                }
                break;
            case 4:
                cout << "1 - Milk" << endl;
                cout << "2 - Cheese" << endl;
                cin >> choice;
                switch (choice) {
                    case 1:
                        cout << "How many?: ";
                        cin >> quantity;
                        inventory.milk += quantity;
                        break;
                    case 2:
                        cout << "How many?: ";
                        cin >> quantity;
                        inventory.cheese += quantity;
                        break;
                    default:
                        cout << "Invalid Input!" << endl;
                        break;
                }
                break;
            case 5:
                cout << "1 - Bisuits" << endl;
                cin >> choice;
                switch (choice) {
                    case 1:
                        cout << "How many?: ";
                        cin >> quantity;
                        inventory.biscuits += quantity;
                        break;
                }
                break;
            case 6:
                cout << "1 - Apple Juice" << endl;
                cin >> choice;
                switch (choice) {
                    case 1:
                        cout << "How many?: ";
                        cin >> quantity;
                        inventory.apple_juice += quantity;
                        break;
                }
                break;
            case 7:
                cout << "Meat + Fish:" << endl;
                cout << "Cow - " << inventory.cow << endl;
                cout << "Pig - " << inventory.pig << endl;
                cout << "Chicken - " << inventory.chicken << endl;

                cout << "Grain:" << endl;
                cout << "Corn - " << inventory.corn << endl;
                cout << "Rice - " << inventory.rice << endl;
                cout << "Wild Rice - " << inventory.wild_rice << endl;
                cout << "Oats - " << inventory.oats << endl;
                
                cout << "Fuit:" << endl;
                cout << "Strawberries - " << inventory.strawberries << endl;
                cout << "Apples - " << inventory.apples << endl;
                cout << "Peaches - " << inventory.peaches << endl;

                cout << "Dairy Products:" << endl;
                cout << "Milk - " << inventory.milk << endl;
                cout << "Cheese - " << inventory.cheese << endl;
                
                cout << "Processed + Cooked Food" << endl;
                cout << "Biscuits - " << inventory.biscuits << endl;

                cout << "Drinks:" << endl;
                cout << "Apple Juice - " << inventory.apple_juice << endl;
                system("Pause");
                system("cls");
                break;
            case 8:
                break;
            default:
                cout << "Invalid Input!" << endl;
                break;
        }


    } while (input != 8);
}

// # WORLD GEN

// char getTile() {
//     int r = rand() % 100;
//     if (r < 20) return 'W';
//     else if (r < 45) return 'F';
//     else if (r < 65) return 'M';
//     else return 'P';
// }

// void generateWorld(int width, int height) {
//     for (int y = 0; y < height; y++) {
//         for (int x = 0; x < width; x++) {
//             cout << getTile() << ' ';
//         }
//         cout << '\n';
//     }
// }

const int WIDTH = 20;
const int HEIGHT = 10;
char world[HEIGHT][WIDTH];

float getSmoothNoise(int x, int y, unsigned int seed) {
    srand(x * 49632 + y * 325176 + seed); 
    return static_cast<float>(rand()) / RAND_MAX;
}

char getTerrain(float noise) {
    if (noise < 0.2f) return 'W';   // Water
    if (noise < 0.4f) return '*';   // Plains
    if (noise < 0.6f) return 'F';   // Forest
    if (noise < 0.8f) return '^';   // Hills
    return '#';                     // Mountain
}

string getRandomFromList(const string options[], int size, unsigned int seed) {
    srand(seed);
    return options[rand() % size];
}

World generateWorldMeta(unsigned int seed) {
    World worldMeta;

    const string planetTypes[] = {"Icy", "Rocky", "Volcanic", "Oceanic", "Desert"};
    const string atmospheres[] = {"Breathable", "Thin", "Toxic", "None"};

    worldMeta.name = "Planet-" + to_string(seed % 10000);
    worldMeta.type = getRandomFromList(planetTypes, 5, seed + 1);
    worldMeta.atmosphere = getRandomFromList(atmospheres, 4, seed + 2);

    srand(seed + 3);
    worldMeta.gravity = 0.5f + static_cast<float>(rand()) / RAND_MAX;      // 0.5 to 1.5
    worldMeta.avgTemperature = -50 + rand() % 151;                         // -50 to 100 C
    worldMeta.dayLength = 10 + rand() % 100;                               // 10 to 110 minutes
    worldMeta.radiationLevel = rand() % 4;                                 // 0–3

    return worldMeta;
}

void generateTerrain(unsigned int seed) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            float noise = getSmoothNoise(x, y, seed);
            world[y][x] = getTerrain(noise);
        }
    }
}

void printWorldMap() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            std::cout << world[y][x] << ' ';
        }
        std::cout << '\n';
    }
}

void printWorldMeta(const World& w) {
    std::cout << "Planet Name: " << w.name << '\n';
    std::cout << "Type: " << w.type << '\n';
    std::cout << "Atmosphere: " << w.atmosphere << '\n';
    std::cout << "Gravity: " << w.gravity << '\n';
    std::cout << "Average Temp: " << w.avgTemperature << " C\n";
    std::cout << "Day Length: " << w.dayLength << " min\n";
    std::cout << "Radiation Level: " << w.radiationLevel << "\n\n";
}

void start() {
    int input;
    do {
        system("cls");
        cout << "**********************************" << endl;
        cout << "**********************************" << endl;
        setColor()
        cout << "*      Space Colony Simulator    *" << endl;
        cout << "**********************************" << endl;
        cout << "**********************************" << endl;
        cout << "1 - Embark" << endl;
        cout << "2 - About" << endl;
        cout << "3 - Quit" << endl;
        input = getValidNumber();

        switch (input) {
            case 1:
                break;
            case 2:
                system("cls");
                cout << "You are in charge of a human colony on a distant planet.\nYour goal is to keep the colony alive by managing resources,\npopulation, and random disasters." << endl;
                system("pause");
                system("cls");
                break;
            case 3:
                exit(0);
                break;
            default:
                cout << "Invalid Input" << endl;
                system("Pause");
                break;
        }
    } while (input != 1);
}