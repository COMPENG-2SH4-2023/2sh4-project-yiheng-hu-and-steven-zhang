#ifndef FOOD_H
#define FOOD_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "MacUILib.h"


class Food
{
    public:
        Food();
        ~Food();

        void generateFood(objPos blockOff); 

        void getFoodPos(objPos &returnPos);     // Reference for food position
        objPos getFood();       // Return food position

    private:
        objPos foodPos;

};


#endif