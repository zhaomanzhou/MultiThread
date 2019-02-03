#include <iostream>
#include "Buffer.h"


Buffer::Buffer()
{
    for(int i = 0; i < 4; i++)
    {
        bufferBucket[i] = 0;
    }
    addedNum = 0;
    removeNum = 0;
}

bool Buffer::canAdd(const int * part)
{
    for(int i = 0; i < 4; i++)
    {
       if(part[i] != 0)
       {
           if(bufferBucket[i] != cap[i])
               return true;
       }
    }
    return false;
}

bool Buffer::add(int *part, int* remain)
{

    bool flag = true;
    for(int i = 0; i < 4; i++)
    {
        if(bufferBucket[i] + part[i] <= cap[i])
        {
            bufferBucket[i] += part[i];
            addedNum += part[i];
        }
        else
        {
            remain[i] = part[i] - (cap[i] - bufferBucket[i]);
            addedNum += (cap[i] - bufferBucket[i]);
            bufferBucket[i] = cap[i];
            flag = false;
        }
    }
    added = true;
    return flag;
}


void Buffer::bufferState()
{
    std::cout<<"Buffer State:(";
    for(int i = 0; i < 3; i++)
        std::cout<<bufferBucket[i]<<",";
    std::cout<<bufferBucket[3]<<")"<<std::endl;
}


bool Buffer::canRemove(int * part)
{
    for(int i = 0; i < 4; i++)
    {
        if(part[i] != 0)
        {
            if(bufferBucket[i] != 0)
                return true;
        }
    }
    return false;
}

bool Buffer::remove(int * part, int* remain)
{
    bool flag = true;
    for(int i = 0; i < 4; i++)
    {
        if(bufferBucket[i] - part[i] >= 0)
        {
            bufferBucket[i] -= part[i];
            removeNum += part[i];

        }
        else
        {
            remain[i] = part[i] - bufferBucket[i];
            removeNum += bufferBucket[i];
            bufferBucket[i] = 0;
            flag = false;
        }
    }
    added = false;
    return flag;
}


bool Buffer::hasAdded()
{
    return added;
}

bool Buffer::addTerminate()
{
    return addedNum == 20*4*5;

}

bool Buffer::removeTerminate()
{

    return removeNum == 16*4*5;
}
