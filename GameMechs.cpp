#include "GameMechs.h"

GameMechs::GameMechs()
{
    input = 0;
    score = 0;

    exitFlag = false;
    loseFlag = false;
    
    boardSizeX = 20;
    boardSizeY = 10;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    score = 0;

    exitFlag = false;
    loseFlag = false;

    boardSizeX = boardX;
    boardSizeY = boardY;
}

// do you need a destructor?


GameMechs::~GameMechs()
{
    
}



bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStates()
{
    return loseFlag;
}



char GameMechs::getInput()
{
    if (MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }

    return input;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}



int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}



void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}



int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}


