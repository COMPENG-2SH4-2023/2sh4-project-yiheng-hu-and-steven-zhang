#include "Player.h"



Player::Player(GameMechs* thisGMRef, Food* thisFood)
{
    mainGameMechsRef = thisGMRef;
    playerFood = thisFood;
    myDir = STOP;
    playerPosList = new objPosArrayList();

    // Initialize the head
    objPos initialPos;

    initialPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');

    playerPosList->insertHead(initialPos);
}


Player::~Player()
{
    delete playerPosList;
}

void Player::getPlayerPos(objPosArrayList &returnPosList)
{
    // return the reference to the playerPos arrray list

    returnPosList = *playerPosList;
}

objPosArrayList* Player::getPlayerList()
{
    return playerPosList;
}



void Player::updatePlayerDir()
{
    // PPA3 input processing logic 

    
    switch(mainGameMechsRef->getInput())
    {
        case 27: // Esc ASCII value
            mainGameMechsRef->setExitTrue();
            break;

        case 'w':
            if (myDir != DOWN)
            {
                myDir = UP;
            }
            break;

        case 'a':
            if (myDir != RIGHT)
            {
                myDir = LEFT;
            }
            break;

        case 's':
            if (myDir != UP)
            {
                myDir = DOWN;
            }
            break;

        case 'd':
            if (myDir != LEFT)
            {
                myDir = RIGHT;
            }
            break;
        default:  // Add default case even if no actions will be taken (debugging convenience)
            break;
    }
    
   
}

void Player::movePlayer()
{
    int bucketSize = playerFood->getBucketSize();

    objPos headPos;
    objPos nextHeadPos;
    objPos playerFoodPos;

    objPosArrayList* playerFoodList;

    playerFoodList = playerFood->getBucket();

    playerPosList->getHeadElement(headPos);
    

    // PPA3 Finite State Machine logic
    switch(myDir)
    {
        case STOP: 
            //MacUILib_printf("Press w/a/s/d to move\n");
        break;

        case UP: 
            if (headPos.y == 1)     // Head position is 1 ahead next position, therefore start from index 1
            {
                headPos.y = 13;     // Same reason, so that start from last index
            }
            else
            {
                headPos.y--;
            }

            checkSelfCollision(headPos);        // Always check self collision first

            foodConsumption(playerFoodList, playerFoodPos, headPos, nextHeadPos, bucketSize);
        break;


        case LEFT:
            if (headPos.x == 1)
            {
                headPos.x = 28;
            }
            else
            {
                headPos.x--;
            }

            checkSelfCollision(headPos);

            foodConsumption(playerFoodList, playerFoodPos, headPos, nextHeadPos, bucketSize);
        break;

        case DOWN:
            if (headPos.y == 13)
            {
                headPos.y = 1;
            }
            else
            {
                headPos.y++;
            }

            checkSelfCollision(headPos);

            foodConsumption(playerFoodList, playerFoodPos, headPos, nextHeadPos, bucketSize);
        break;

        case RIGHT:
            if (headPos.x == 28)
            {
                headPos.x = 1;
            }
            else
            {
                headPos.x++;
            }

            checkSelfCollision(headPos);

            foodConsumption(playerFoodList, playerFoodPos, headPos, nextHeadPos, bucketSize);
        break;
            
        default:  // Add default case even if no actions will be taken (debugginh convenience)
            MacUILib_printf("Unknown Mode\n");
        break;
    }
}


// Update head position each time moving
void Player::updateHead(objPos headPos, objPos nextHead)
{
    nextHead.setObjPos(headPos.x, headPos.y, headPos.symbol);
    playerPosList->insertHead(nextHead);
}


bool Player::checkSelfCollision(objPos headPos)
{
    int size = playerPosList->getSize();        // List size
    objPos bodyPos;     // Reference for the body position, start from index 1

    for (int i = 1; i < size; i++)
    {
        playerPosList->getElement(bodyPos, i);

        if (headPos.isPosEqual(&bodyPos))       // Check the collosion fpr each body element
        {
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
            return true;
        }
    }

    return false;
}



void Player::foodConsumption(objPosArrayList* thisBucket, objPos thisFood, objPos thisHead, objPos nextHead, int bucketSize)
{
    // Check food consumption
    for (int bucketIndex = 0; bucketIndex < bucketSize; bucketIndex++)
    {
        thisBucket->getElement(thisFood, bucketIndex);     // Access each food element in the bucket

        if (thisHead.isPosEqual(&thisFood)) 
        {
            if (thisFood.symbol == 'A')                    // While eating food 'A', increase 10 points
            {
                mainGameMechsRef->bonusIncrementScore();        
            }

            else if (thisFood.symbol == 'B')               // While eating food 'B', increase 1 point without growing
            {
                mainGameMechsRef->incrementScore();
                playerPosList->removeTail();
            }

            else
            {
                mainGameMechsRef->incrementScore();
            }

            updateHead(thisHead, nextHead);                 // Insert head without removing tail
            playerFood->generateFood(playerPosList);        // Generate new food
            break;      // Stop checking once consumption happen
        }
    }

    // Normal movement (no food consumption)
    updateHead(thisHead, nextHead);
    playerPosList->removeTail();
}