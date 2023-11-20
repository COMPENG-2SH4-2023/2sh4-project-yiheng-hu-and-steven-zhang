#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* myGame;
Player* myPlayer;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGame->getExitFlagStatus() == false && myGame->getLoseFlagStates() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGame = new GameMechs(30, 15);
    myPlayer = new Player(myGame);

}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
}

void DrawScreen(void)
{
    int i, j;       // i is row, j is column
    char symbol = '#';

    
    objPos board;
    objPos space;
    objPos newline;
    

    objPos tempPos;
    myPlayer->getPlayerPos(tempPos);

    board.setObjPos(j, i, symbol);
    newline.setObjPos(j, i, '\n');
    space.setObjPos(j, i, ' ');


    MacUILib_clearScreen();    

    for (i = 0; i < myGame->getBoardSizeY(); i++)
    {
        for (j = 0; j < myGame->getBoardSizeX(); j++)
        {
            if (i == 0 || i == 14)       // Row 1 and 15
            {
                MacUILib_printf("%c", board.symbol);

                if (j == 29)
                {
                    MacUILib_printf("%c", newline.symbol);      // Add space at the last colum
                }
            }

            else if (i == tempPos.y && j == tempPos.x)
            {
                MacUILib_printf("%c", tempPos.symbol);      // Add player position
            }

            else
            {
                if (j == 0)      // First column
                {
                    MacUILib_printf("%c", board.symbol);
                }

                else if (j == 29)       // Last column (add newline)
                {
                    MacUILib_printf("%c%c", board.symbol, newline.symbol);
                }

                else
                {
                    MacUILib_printf("%c", space.symbol);
                }
            }
        }
    }

    MacUILib_printf("Your score is: %d\n", myGame->getScore());


    if (myGame->getScore() == 20)
    {
        MacUILib_printf("You lose the game, keep up next time!\n");
        myGame->setLoseFlag();
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    //MacUILib_clearScreen();    
  
    MacUILib_uninit();
}
