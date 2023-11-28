#include "Food.h"


Food::Food()
{
    objPos initialHeadPos;
    initialHeadPos.setObjPos(5, 5, '1');

    foodBucket = new objPosArrayList();

    foodBucket->insertHead(initialHeadPos);
}

Food::~Food()
{
    delete foodBucket;
}



void Food::generateFood(objPosArrayList* thisList)
{
    int done = 0;
    int snakeSize = thisList->getSize();
    int bucketSize = foodBucket->getSize();

    objPos snakeBodyPos;
    objPos newFoodPos;
    objPos oldFoodPos;

    newFoodPos.setObjPos(1, 1, '0');


    srand(time(NULL));


    while (!done)
    {
        newFoodPos.x = 1 + rand() % 28;        // range[1, 28]
        newFoodPos.y = 1 + rand() % 13;        // range[1, 13]



        for (int bucketIndex = 0; bucketIndex < bucketSize; bucketIndex++)
        {
            foodBucket->getElement(oldFoodPos, bucketIndex);

            if (newFoodPos.x == oldFoodPos.x && newFoodPos.y == oldFoodPos.y)
            {
                continue;
            }
        }

        for (int snakeIndex = 0; snakeIndex < snakeSize; snakeIndex++)
        {
            thisList->getElement(snakeBodyPos, snakeIndex);

            if (newFoodPos.isPosEqual(&snakeBodyPos))
            {
                continue;
            }
        }

        foodBucket->insertHead(newFoodPos);
        foodBucket->removeTail();

        done = 1;
    }
}


objPosArrayList* Food::getBucket()
{
    return foodBucket;
}

int Food::getBucketSize()
{
    int size = foodBucket->getSize();
    return size;
}