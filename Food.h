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

        void generateFood(objPosArrayList* thisList); 

        int getBucketSize();
        objPosArrayList* getBucket();       // Return the bucket

        void overlapCheck(int size, objPos oldPos, objPos newPos, objPosArrayList* list);

    private:
        objPosArrayList* foodBucket;

};


#endif