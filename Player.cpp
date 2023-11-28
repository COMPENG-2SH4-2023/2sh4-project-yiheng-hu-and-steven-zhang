#include "Player.h"



Player::Player(GameMechs* thisGMRef, Food* thisFood)
{
    mainGameMechsRef = thisGMRef;
    playerFood = thisFood;
    myDir = STOP;
    playerPosList = new objPosArrayList();

    // more actions to be included
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
        default:  // Add default case even if no actions will be taken (debugginh convenience)
            break;
    }
    
   
}

void Player::movePlayer()
{
    objPos headPos;
    objPos nextHeadPos;
    objPos playerFoodPos;

    objPosArrayList* playerFoodList;

    playerFoodList = playerFood->getBucket();
    playerFoodList->getHeadElement(playerFoodPos);

    playerPosList->getHeadElement(headPos);
    

    // PPA3 Finite State Machine logic
    switch(myDir)
    {
        case STOP: 
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

            checkSelfCollision(headPos);

            if (headPos.x == playerFoodPos.x && headPos.y == playerFoodPos.y)       // Check food consumption
            {
                mainGameMechsRef->incrementScore();

                updateHead(headPos, nextHeadPos);
                playerFood->generateFood(playerPosList);      // Generate new food
            }

            else
            {
                updateHead(headPos, nextHeadPos);
                playerPosList->removeTail();
            }
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

            if (headPos.x == playerFoodPos.x && headPos.y == playerFoodPos.y)
            {
                mainGameMechsRef->incrementScore();

                updateHead(headPos, nextHeadPos);
                playerFood->generateFood(playerPosList);
            }

            else
            {
                updateHead(headPos, nextHeadPos);
                playerPosList->removeTail();
            }
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

            if (headPos.x == playerFoodPos.x && headPos.y == playerFoodPos.y)
            {
                mainGameMechsRef->incrementScore();

                updateHead(headPos, nextHeadPos);
                playerFood->generateFood(playerPosList);
            }

            else
            {
                updateHead(headPos, nextHeadPos);
                playerPosList->removeTail();
            }
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

            if (headPos.x == playerFoodPos.x && headPos.y == playerFoodPos.y)
            {
                mainGameMechsRef->incrementScore();

                updateHead(headPos, nextHeadPos);
                playerFood->generateFood(playerPosList);
            }

            else
            {
                updateHead(headPos, nextHeadPos);
                playerPosList->removeTail();
            }
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