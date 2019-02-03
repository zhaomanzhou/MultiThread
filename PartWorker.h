//
// Created by zmz on 2018/12/10.
//

#ifndef MULTITHREAD_PARTWORKER_H
#define MULTITHREAD_PARTWORKER_H

class PartWorker
{
public:
    PartWorker();
    void operator()(int i);
private:
    int currentPart[4]{};
    int placePart[4]{};
    void produceValid();
    void produce();
    bool validate();
    int id;

};

#endif //MULTITHREAD_PARTWORKER_H
