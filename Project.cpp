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
objPosArrayList* playerList;     // Global pointer to the player list



void Initialize(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{
    Initialize();

    while(myGame->getExitFlagStatus() == false && myGame->getLoseFlagStates() == false)  
    {
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
    myFood = new Food();
    myPlayer = new Player(myGame, myFood);

    playerList = myPlayer->getPlayerList();     // For initial food generation

    myFood->generateFood(playerList);     // Avoid overlapping initial head position
}




void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
}



void DrawScreen(void)
{
    objPosArrayList* foodList;   // Pointer to the food bucket

    objPos headPos;         // Reference for the head position of the snake 
    objPos snakePos;        // Reference for the body position of the snake
    objPos foodPos;         // Reference for food position of the bucket

    playerList->getHeadElement(headPos);        // Get new head position in each game loop

    foodList = myFood->getBucket();             // Get new food list in each game loop
    foodList->getHeadElement(foodPos);          // Get new food position
    

    MacUILib_clearScreen();    


    for (int i = 0; i < myGame->getBoardSizeY(); i++)       // i is row
    {
        for (int j = 0; j < myGame->getBoardSizeX(); j++)   // j is column
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




            for (int foodIndex = 0; foodIndex < foodList->getSize(); foodIndex++)
            {
                foodList->getElement(foodPos, foodIndex);       // Access each food element from the head

                if (i == foodPos.y && j == foodPos.x)
                {
                    MacUILib_printf("%c", foodPos.symbol);      // Add each food position
                    isCellFilled = true;
                    break;
                }
            }


            for (int listIndex = 0; listIndex < playerList->getSize(); listIndex++)
            {
                playerList->getElement(snakePos, listIndex);      // Access each snake element from the head

                if (i == snakePos.y && j == snakePos.x)
                {
                    MacUILib_printf("%c", snakePos.symbol);      // Add each snake position
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

    if (myGame->getExitFlagStatus() == true && myGame->getLoseFlagStates() == true)     // Lose message
    {
        MacUILib_printf("\nYou lose the game, keep up!\n");
    }

    if (myGame->getExitFlagStatus() == true && myGame->getLoseFlagStates() == false)     // Manually end game message
    {
        MacUILib_printf("\nYou end the game manually!\n");
    }

    MacUILib_printf("\n///////Debugging message///////\n");
    MacUILib_printf("Snake size: %d\n", playerList->getSize());
    MacUILib_printf("Head position %c: [%d %d]\n", headPos.symbol, headPos.x, headPos.y);
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{ 
    MacUILib_uninit();
}