//
// Created by zmz on 2018/12/10.
//

#ifndef MULTITHREAD_BUFFER_H
#define MULTITHREAD_BUFFER_H

#include <mutex>

class Buffer{
private:
    int bufferBucket[4];
    int cap[4] = {6, 5, 4, 3};
    bool added;
    int addedNum;
    int removeNum;


public:
    Buffer();
   bool canAdd(const int *);
   bool add(int *, int*);
   bool canRemove(int*);
   bool remove(int*, int*);
   void bufferState();
   bool hasAdded();
   bool addTerminate();
   bool removeTerminate();

};
#endif //MULTITHREAD_BUFFER_H
