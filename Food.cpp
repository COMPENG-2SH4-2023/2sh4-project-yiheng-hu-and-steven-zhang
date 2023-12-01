#include "Food.h"


Food::Food()
{
    objPos initialHeadPos;
    objPos bodyPos;
    initialHeadPos.setObjPos(5, 5, '1');

    foodBucket = new objPosArrayList();

    // Initialize 5 food elements
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
            newFoodPos.x = 1 + rand() % 28;        // range[1, 28]
            newFoodPos.y = 1 + rand() % 13;        // range[1, 13]
            newFoodPos.setSymbol('0');             // Assign the default symbol


            overlapCheck(bucketSize, oldFoodPos, newFoodPos, foodBucket);   // Check if overlap the other food
            overlapCheck(snakeSize, snakeBodyPos, newFoodPos, thisList);    // Check if overlap the snake

            // Change the symbols of the first two food elements
            if (i == 0)
            {
                newFoodPos.setSymbol('A');
            }

            else if (i == 1)
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


void Food::overlapCheck(int size, objPos oldPos, objPos newPos, objPosArrayList* list)
{
    for (int i = 0; i < size; i++)
    {
        list->getElement(oldPos, i);    // Access each element in the list

        if (newPos.isPosEqual(&oldPos))
        {
            continue;       // Continue the loop (this function normally used in the loop)
        }
    }
}