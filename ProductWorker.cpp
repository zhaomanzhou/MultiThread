#include <cstdlib>
#include "ProducetWorker.h"

ProductWorker::ProductWorker()
{
}


void ProductWorker::operator()(int id)
{
    this->id = id;
}

void ProductWorker::produceValid()
{
    while (!validate())
        produce();
}

void ProductWorker::produce()
{
    for(int i = 0; i < 4; i++)
    {
        currentPart[i] = rand()%4;
    }
}

bool ProductWorker::validate()
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
    return index == 3;
}
