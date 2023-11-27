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
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

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
        ~GameMechs();
        
        bool getExitFlagStatus();
        bool getLoseFlagStates();
        void setExitTrue();
        void setLoseFlag();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getScore();
        void incrementScore();
        void bonusIncrementScore();

        int getBoardSizeX();
        int getBoardSizeY();
      

};

#endif