#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;
    List = new objPos[arrayCapacity];
}

objPosArrayList::~objPosArrayList()
{
    for (int i = 0; i < arrayCapacity; i++)
    {
        delete [] &List[i];
    }
    delete [] &List;
}

int objPosArrayList::getSize()
{
    return listSize;
}



void objPosArrayList::insertHead(objPos thisPos)
{
    listSize++;
    objPos curPos = List[0];        // Store the head position initially
    objPos nextPos;

    for (int i = 0; i < listSize; i++)
    {
        nextPos = List[i + 1];       // Store the next position
        List[i + 1] = curPos;       // Change the next position to the origional current position
        curPos = nextPos;        // Store the next position in order for the changing of the one after next
    }
    
    List[0] = thisPos;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    listSize++;
    
    List[listSize - 1] = thisPos;
}

void objPosArrayList::removeHead()
{
    objPos curPos = List[1];        // Store the second position initially
    objPos nextPos;

    // Set 2nd element as 3rd element, 3rd element as 4th element, and so on. Cannot access the last element
    for (int i = 0; i < listSize - 1; i++)  
    {
        nextPos = List[i + 2];       // Store the one after next position
        List[i + 0] = curPos;       // Change the current element as next element
        curPos = nextPos;        // Store the one after next position in order for the changing of the next element
    }

    List[listSize - 1] = objPos();      // Reset the last element to 0

    listSize--;
}

void objPosArrayList::removeTail()
{
    List[listSize - 1] = objPos();      // Reset the last element to 0

    listSize--;
}



void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos = List[0];
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos = List[listSize - 1];
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos = List[index];
}