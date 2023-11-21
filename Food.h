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
        void getFoodPos(objPos &returnPos);

    private:
        objPos foodPos;

};


#endif