#include "Food.h"


Food::Food()
{
    objPos initialHeadPos;
    objPos bodyPos;
    initialHeadPos.setObjPos(5, 5, '1');

    foodBucket = new objPosArrayList();

    foodBucket->insertHead(initialHeadPos);

    for (int i = 1; i < 5; i++)
    {
        bodyPos.setObjPos(5 + i, 5 + i, '1' + i);
        foodBucket->insertTail(bodyPos);
    }
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


    srand(time(NULL));


    while (!done)
    {
        for (int i = bucketSize - 1; i >= 0; i--)
        {
            newFoodPos.setObjPos(1, 1, '0');

            newFoodPos.x = 1 + rand() % 28;        // range[1, 28]
            newFoodPos.y = 1 + rand() % 13;        // range[1, 13]



            for (int bucketIndex = 0; bucketIndex < bucketSize; bucketIndex++)      // Check if overlap the other elements
            {
                foodBucket->getElement(oldFoodPos, bucketIndex);

                if (newFoodPos.isPosEqual(&oldFoodPos))
                {
                    continue;
                }
            }

            for (int snakeIndex = 0; snakeIndex < snakeSize; snakeIndex++)      // Check if overlap the snake body
            {
                thisList->getElement(snakeBodyPos, snakeIndex);

                if (newFoodPos.isPosEqual(&snakeBodyPos))
                {
                    continue;
                }
            }

            if (i == 1)
            {
                newFoodPos.setSymbol('A');
            }

            if (i == 0)
            {
                newFoodPos.setSymbol('B');
            }

            foodBucket->insertHead(newFoodPos);
            foodBucket->removeTail();
        }
        
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