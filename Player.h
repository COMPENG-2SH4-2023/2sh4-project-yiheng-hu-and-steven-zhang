#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "MacUILib.h"
#include "Food.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef, Food* thisFood);
        ~Player();


        void getPlayerPos(objPosArrayList &returnPosList);      // Reference for the player list
        objPosArrayList* getPlayerList();       // Return player list

        void updatePlayerDir();
        void movePlayer();
        void updateHead(objPos headPos, objPos nextHead);

        bool checkSelfCollision(objPos headPos);

    private:
        //objPos playerPos;   // Upgrade this in iteration 3.      
        objPosArrayList* playerPosList; 
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
        Food* playerFood; 
};

#endif