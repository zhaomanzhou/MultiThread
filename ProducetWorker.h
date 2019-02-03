#ifndef MULTITHREAD_PRODUCETWORKER_H
#define MULTITHREAD_PRODUCETWORKER_H

class ProductWorker{
public:
    ProductWorker();
    void operator()(int id);
private:
    int currentPart[4]{};
    int pickupPart[4]{};
    void produceValid();
    void produce();
    bool validate();
    int id;
};
#endif //MULTITHREAD_PRODUCETWORKER_H
