#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "MacUILib.h"
#include "Food.h"

class Player
{
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef, Food* thisFood);
        ~Player();


        void getPlayerPos(objPosArrayList &returnPosList);      // Reference for the player list
        objPosArrayList* getPlayerList();       // Return player list

        void updatePlayerDir();
        void movePlayer();
        void updateHead(objPos headPos, objPos nextHead);

        void foodConsumption(objPosArrayList* thisBucket, objPos thisFood, objPos thisHead, objPos nextHead, int bucketSize);

        bool checkSelfCollision(objPos headPos);

    private:      
        objPosArrayList* playerPosList; 
        enum Dir myDir;

        // References to the Main Game Mechanisms and food
        GameMechs* mainGameMechsRef;
        Food* playerFood; 
};

#endif