#include "Food.h"


Food::Food()
{
    foodPos.setObjPos(5, 5, '0');
}

Food::~Food()
{
    //delete &foodPos;
}



void Food::generateFood(objPos blockOff)
{
    int done = 0;

    srand(time(NULL));


    while (!done)
    {
        foodPos.x = 1 + rand() % 28;        // range[1, 28]
        foodPos.y = 1 + rand() % 13;        // range[1, 13]

        if (foodPos.isPosEqual(&blockOff))
        {
            continue;
        }

        else
        {
            done = 1;
        }
    }
}


objPos Food::getFood()
{
    return foodPos;
}


void Food::getFoodPos(objPos &returnPos)
{
    // return the reference to the foodPos arrray list
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}