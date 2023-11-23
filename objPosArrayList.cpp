#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;
    List = new objPos[arrayCapacity];
}

objPosArrayList::objPosArrayList(const objPosArrayList &list)
{
    listSize = list.listSize;
    arrayCapacity = list.arrayCapacity;
    List = new objPos[ARRAY_MAX_CAP];


    for (int i = 0; i < listSize; i++)
    {
        List[i] = list.List[i];
    }
    
}

objPosArrayList::~objPosArrayList()
{
    delete [] List;
}

int objPosArrayList::getSize()
{
    return listSize;
}



void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize == arrayCapacity)       // Check if the array is full
    {
        cout << "Array full..." << endl;
        return;
    }


    // Pushing all elements back by one slot, overwriting the value in i+1 with that in i
    for (int i = listSize; i > 0; i--)
    {
        List[i] = List[i - 1];
    }
    
    listSize++;
    List[0] = thisPos;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize == arrayCapacity)       // Check if the array is full
    {
        cout << "Array full..." << endl;
        return;
    }

    listSize++;
    List[listSize - 1] = thisPos;
}

void objPosArrayList::removeHead()
{
    if (listSize == 0)       // Check if the array is empty
    {
        cout << "Empty array!" << endl;
        return;
    }


    // Set 2nd element as 3rd element, 3rd element as 4th element, and so on. Cannot access the last element
    for (int i = 0; i < listSize - 1; i++)  
    {
        List[i] = List[i + 1];
    }

    //List[listSize - 1] = objPos();      // Lazy delete, don't reset the last element to 0

    listSize--;
}

void objPosArrayList::removeTail()
{
    if (listSize == 0)       // Check if the array is empty
    {
        cout << "Empty array!" << endl;
        return;
    }


    //List[listSize - 1] = objPos();      // Lazy delete, don't reset the last element to 0

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