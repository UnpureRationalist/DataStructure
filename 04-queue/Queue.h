#ifndef QUEUE
#define QUEUE
#include <iostream>
using namespace std;
template <class T>
class Queue
{
protected:
    void memoryError()
    {
        cerr << "Memory Error!\n";
        exit(-1);
    }

    void emptyError()
    {
        cerr << "Queue is empty!\n";
        exit(-1);
    }
    
public:
    Queue() {}

    virtual ~Queue() {}

    virtual bool isEmpty() = 0;

    virtual int size() = 0;

    virtual void push(T value) = 0;

    virtual T pop() = 0;
};

#endif