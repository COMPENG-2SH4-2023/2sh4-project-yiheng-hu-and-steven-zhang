#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000
#define DEFAULT_SIZE 50

GameMechs* myGame;      // Global pointer to GameMechs class
Player* myPlayer;       // Global pointer to Plyer class
Food* myFood;           // Global pointer to Food class


objPos tempFoodPos;     // Reference for the food position
objPos headPos;         // Reference for the head position in the list
objPos bodyPos;

objPosArrayList playerList;     // Reference for the player list


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

    myPlayer->getPlayerPos(playerList);     // Reference to the player list
    playerList.getHeadElement(headPos);     // Reference to the head position, for initial food generation

    /*
    for (int i = 1; i < 5; i++)
    {
        bodyPos.setObjPos(headPos.x, headPos.y + i, '8');
        playerList.insertTail(bodyPos);
    }
    */

    myFood->generateFood(headPos);     // Avoid overlapping initial head position
    myFood->getFoodPos(tempFoodPos);
}



void GetInput(void)
{
   
}



void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    playerList.getHeadElement(headPos);     // Reference to the head position, for debugging
}



void DrawScreen(void)
{
    int i, j;       // i is row, j is column
    int listIndex;


    MacUILib_clearScreen();    


    for (i = 0; i < myGame->getBoardSizeY(); i++)
    {
        for (j = 0; j < myGame->getBoardSizeX(); j++)
        {
            bool isCellFilled = false;      // Check if the cell is been taken


            if (i == 0 || i == 14)       // Row 1 and 15
            {
                MacUILib_printf("#");
                isCellFilled = true;

                if (j == 29)
                {
                    MacUILib_printf("\n");      // Add new line at the last column
                    isCellFilled = true;
                }
            }

            else if (j == 0)        // Add '#' at each row of the first column, row index in this condition: [1, 13]
            {
                MacUILib_printf("#");
                isCellFilled = true;
            }

            else if (j == 29)       // Add '#' and new line at each row of the last column, row index in this condition: [1, 13]
            {
                MacUILib_printf("#\n");
                isCellFilled = true;
            }


            /*
            if (i == headPos.y && j == headPos.x)
            {
                MacUILib_printf("%c", headPos.symbol);      // Add food position
                isCellFilled = true;
            }
            */

            else if (i == tempFoodPos.y && j == tempFoodPos.x)
            {
                MacUILib_printf("%c", tempFoodPos.symbol);      // Add food position
                isCellFilled = true;
            }

            for (listIndex = 0; listIndex < playerList.getSize(); listIndex++)
            {
                playerList.getElement(bodyPos, listIndex);      // Access each element from the second element

                if (i == bodyPos.y && j == bodyPos.x)
                {
                    MacUILib_printf("%c", bodyPos.symbol);      // Add element position
                    isCellFilled = true;
                    break;
                }
            }


            
            // Only print space when the cell is not been taken
            if (!isCellFilled)
            {
                MacUILib_printf(" ");
            }
        }
    }

    MacUILib_printf("Your score is: %d\n", myGame->getScore());
    MacUILib_printf("List size: %d\n", playerList.getSize());
    MacUILib_printf("Food position %c: [%d %d]\n", tempFoodPos.symbol, tempFoodPos.x, tempFoodPos.y);

    MacUILib_printf("\n");
    MacUILib_printf("Head position %c: [%d %d]\n", headPos.symbol, headPos.x, headPos.y);
   
    for (int i = 1; i < playerList.getSize(); i++)
    {
        playerList.getElement(bodyPos, i);
        MacUILib_printf("Body %d position %c: [%d %d]\n", i, bodyPos.symbol, bodyPos.x, bodyPos.y);
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{ 
    MacUILib_uninit();
}
