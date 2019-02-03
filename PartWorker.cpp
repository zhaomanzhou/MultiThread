#include <cstdlib>
#include <iostream>
#include "PartWorker.h"
#include "Buffer.h"


PartWorker::PartWorker()
{
    produceValid();
}
void PartWorker::operator()(int i)
{

//    this->id = id;
//    extern Buffer b;
//    b.bufferState();
//    std::cout<<std::endl;
//    std::cout<<b.canAdd(placePart);
//    if(b.canAdd(placePart))
//    {
//        b.add(placePart);
//    }


}
void PartWorker::produceValid()
{
    while (!validate())
        produce();
    for(int i = 0; i < 4; i++)
    {
        placePart[currentPart[i]]++;
    }
}

void PartWorker::produce()
{
    for(int i = 0; i < 4; i++)
    {
        currentPart[i] = rand()%4;
    }
}

bool PartWorker::validate()
{
    int temp[4];
    int index = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; i < index; j++)
        {
            if(temp[j] == currentPart[i])
                continue;
            temp[index++] = currentPart[i];
        }
    }
    return index >1 && index <= 3;
}
