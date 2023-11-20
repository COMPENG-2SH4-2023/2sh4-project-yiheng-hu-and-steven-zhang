#include "Player.h"



Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');
}


Player::~Player()
{
    delete mainGameMechsRef;
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list

    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
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
    // PPA3 Finite State Machine logic
    switch(myDir)
    {
        case STOP: 
            break;

        case UP: 
            playerPos.y--;
            mainGameMechsRef->incrementScore();
            if (playerPos.y == 0)
            {
                playerPos.y = 13;
            }
            break;

        case LEFT:
            playerPos.x--;
            if (playerPos.x == 0)
            {
                playerPos.x = 28;
            }
            break;

        case DOWN:
            playerPos.y++;
            if (playerPos.y == 14)
            {
                playerPos.y = 1;
            }
            break;

        case RIGHT:
            playerPos.x++;
            if (playerPos.x == 29)
            {
                playerPos.x = 1;
            }
            break;
            
        default:  // Add default case even if no actions will be taken (debugginh convenience)
            MacUILib_printf("Unknown Mode\n");
            break;
    }
    
}

