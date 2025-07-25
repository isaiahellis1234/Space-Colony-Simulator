#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>

struct Inventory {
    public:
        // # Meat + Fish
        int cow = 0;
        int pig = 0;
        int chicken = 0;

        // # Grain
        int corn = 0;
        int rice = 0;
        int wild_rice = 0;
        int oats = 0;

        // # Fruit
        int strawberries = 0;
        int apples = 0;
        int peaches = 0;

        // # Dairy Products
        int milk = 0;
        int cheese = 0;

        // Processed + Cooked Food
        int biscuits = 0;

        // Drinks
        int apple_juice = 0;
};

#endif