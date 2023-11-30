#ifndef OBJPOS_H
#define OBJPOS_H

class objPos
{
    public:
        int x;
        int y;
        char symbol;

        objPos();
        objPos(objPos &o); // copy constructor
        objPos(int xPos, int yPos, char sym);

        void setObjPos(objPos o);        
        void setObjPos(int xPos, int yPos, char sym); 
        void setSymbol(char sym);

        void getObjPos(objPos &returnPos);      // Pass by reference, provide an empty objPos into this function
        char getSymbol();

        bool isPosEqual(const objPos* refPos);      // Pass by pointer
        
        char getSymbolIfPosEqual(const objPos* refPos);
};

#endif