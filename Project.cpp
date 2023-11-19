#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(exitFlag == false)  
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

    exitFlag = false;
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    
}

void DrawScreen(void)
{
    int i, j;
    char symbol = '#';
    objPos board;
    objPos space;
    objPos newline;

    board.setObjPos(j, i, symbol);
    newline.setObjPos(j, i, '\n');
    space.setObjPos(j, i, ' ');


    MacUILib_clearScreen();    

    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 20; j++)
        {
            if (i == 0 || i == 9)       // Row 1 and 10
            {
                MacUILib_printf("%c", board.symbol);

                if (j == 19)
                {
                    MacUILib_printf("%c", newline.symbol);      // Add space at the last colum
                }
            }


            else
            {
                if (j ==0)      // First column
                {
                    MacUILib_printf("%c", board.symbol);
                }

                else if (j == 19)       // Last column (add newline)
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
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
}
