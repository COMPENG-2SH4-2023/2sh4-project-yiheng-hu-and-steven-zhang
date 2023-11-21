#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* myGame;      // Global pointer to GameMechs class
Player* myPlayer;       // Global pointer to Plyer class
Food* myFood;           // Global pointer to Food class


objPos tempFoodPos;     // Reference for the food position
objPos tempPlyerPos;    // Reference for the player position


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
    myFood = new Food();

    tempPlyerPos.setObjPos(myGame->getBoardSizeX() / 2, myGame->getBoardSizeY() / 2, '*');      // Initialize player position for generating

    myFood->generateFood(tempPlyerPos);     // Avoid overlapping initial player position
    myFood->getFoodPos(tempFoodPos);

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

    
    objPos board;       
    objPos space;
    objPos newline;
    

    myPlayer->getPlayerPos(tempPlyerPos);

    /*
    myFood->generateFood(tempPlyerPos);      // Avoid overlapping player
    myFood->getFoodPos(tempFoodPos);
    */
    
    
    // Assign the same index variable and different characters to these three objects
    board.setObjPos(j, i, '#');
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

            else if (i == tempPlyerPos.y && j == tempPlyerPos.x)
            {
                MacUILib_printf("%c", tempPlyerPos.symbol);      // Add player position
            }

            else if (i == tempFoodPos.y && j == tempFoodPos.x)
            {
                MacUILib_printf("%c", tempFoodPos.symbol);      // Add food position
            }

            else
            {
                if (j == 0)      // Add '#' at each row of the first column
                {
                    MacUILib_printf("%c", board.symbol);
                }

                else if (j == 29)       // Add '#' and new line at each row of the last column
                {
                    MacUILib_printf("%c%c", board.symbol, newline.symbol);
                }

                else
                {
                    MacUILib_printf("%c", space.symbol);    // Add space
                }
            }
        }
    }

    MacUILib_printf("Your score is: %d\n", myGame->getScore());
    MacUILib_printf("Food position: [%d %d]\n", tempFoodPos.x, tempFoodPos.y);
    MacUILib_printf("Player position: [%d %d]\n", tempPlyerPos.x, tempPlyerPos.y);

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
