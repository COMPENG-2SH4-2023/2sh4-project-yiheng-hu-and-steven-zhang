#include "Player.h"



Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
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
    objPos nextPos;
    playerPosList->getHeadElement(headPos);


    // PPA3 Finite State Machine logic
    switch(myDir)
    {
        case STOP: 
            break;

        case UP: 
            if (headPos.y == 1)     // Head position is 1 ahead next position, therefore start from index 1
            {
                headPos.y = 14;     // Same reason, so that start from last index
            }

            nextPos.setObjPos(headPos.x, headPos.y - 1, headPos.symbol);
            playerPosList->insertHead(nextPos);
            playerPosList->removeTail();
            break;

        case LEFT:
            if (headPos.x == 1)
            {
                headPos.x = 29;
            }

            nextPos.setObjPos(headPos.x - 1, headPos.y, headPos.symbol);
            playerPosList->insertHead(nextPos);
            playerPosList->removeTail();
            break;

        case DOWN:
            if (headPos.y == 13)
            {
                headPos.y = 0;
            }

            nextPos.setObjPos(headPos.x, headPos.y + 1, headPos.symbol);
            playerPosList->insertHead(nextPos);
            playerPosList->removeTail();
            break;

        case RIGHT:
            if (headPos.x == 28)
            {
                headPos.x = 0;
            }

            nextPos.setObjPos(headPos.x + 1, headPos.y, headPos.symbol);
            playerPosList->insertHead(nextPos);
            playerPosList->removeTail();
            break;
            
        default:  // Add default case even if no actions will be taken (debugginh convenience)
            MacUILib_printf("Unknown Mode\n");
            break;
    }
    
}

