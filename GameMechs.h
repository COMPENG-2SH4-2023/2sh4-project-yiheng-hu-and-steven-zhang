#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"
#include "MacUILib.h"

using namespace std;


class GameMechs
{
    private:
        char input;
        int score;
        bool exitFlag;
        bool loseFlag;
   
        int boardSizeX;
        int boardSizeY;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        
        bool getExitFlagStatus();
        bool getLoseFlagStates();
        void setExitTrue();
        void setLoseFlag();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getScore();
        void incrementScore();
        void bonusIncrementScore();     // Increase 10 points

        int getBoardSizeX();
        int getBoardSizeY();
};

#endif