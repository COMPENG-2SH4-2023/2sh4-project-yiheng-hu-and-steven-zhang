#include "Food.h"


Food::Food()
{
    objPos initialHeadPos;
    objPos initialBodyPos;
    initialHeadPos.setObjPos(5, 5, '0');
    initialBodyPos.setObjPos(10, 10, '1');

    foodBucket = new objPosArrayList();
    foodBucket->insertHead(initialHeadPos);
    foodBucket->insertTail(initialBodyPos);
}

Food::~Food()
{
    delete foodBucket;
}



void Food::generateFood(objPosArrayList* thisList)
{
    int newFoodPos_x, newFoodPos_y, newSecondPos_x, newSecondPos_y;
    char symbol;
    int done = 0;
    int snakeSize = thisList->getSize();
    int bucketSize = foodBucket->getSize();

    objPos foodPos;
    objPos newFoodPos;
    objPos newSecondPos;

    objPos snakeBodyPos;

    foodBucket->getHeadElement(foodPos);        // Get the old head of the bucket first

    srand(time(NULL));


    while (!done)
    {

        newFoodPos_x = 1 + rand() % 28;        // range[1, 28]
        newFoodPos_y = 1 + rand() % 13;        // range[1, 13]

        newSecondPos_x = 1 + rand() % 28;  
        newSecondPos_y = 1 + rand() % 13;

        symbol = 33 + rand() % 94;  // range[33, 33 + 93 = 126]

        newFoodPos.setObjPos(newFoodPos_x, newFoodPos_y, '0');
        newSecondPos.setObjPos(newSecondPos_x, newSecondPos_y, symbol);

        if (symbol == '0')
        {
            continue;
        }

        else if (newFoodPos_x == newSecondPos_x && newFoodPos_y == newSecondPos_y)
        {
            continue;
        }


        for (int bucketIndex = 0; bucketIndex < foodBucket->getSize(); bucketIndex++)   // Check overlapping previous food position
        {
            foodBucket->getElement(foodPos, bucketIndex);

            if (newFoodPos.isPosEqual(&foodPos) || newSecondPos.isPosEqual(&foodPos))        // Avoid generating at the last position
            {
                continue;
            }
        }


        for (int snakeIndex = 0; snakeIndex < snakeSize; snakeIndex++)
        {
            thisList->getElement(snakeBodyPos, snakeIndex);   // Access each element in the player position list, start from the head

            if (newFoodPos.isPosEqual(&snakeBodyPos) || newSecondPos.isPosEqual(&snakeBodyPos))       // Check the position overlapping
            {
                continue;
            }
        }
        foodBucket->insertHead(newSecondPos);
        foodBucket->insertHead(newFoodPos);        // Insert the new generated position
        foodBucket->removeTail();                  // Remove the old position
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