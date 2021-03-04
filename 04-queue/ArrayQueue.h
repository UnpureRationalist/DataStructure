#ifndef ARRAY_QUEUE
#define ARRAY_QUEUE

#include <iostream>
#include "Queue.h"
using namespace std;

template<class T>
class ArrayQueue : public Queue<T>
{
private:
    T *data = nullptr;
    int head, tail;
    int capacity;

public:
    ArrayQueue(int size)
    {
        data = new (nothrow) T[capacity = size+1];
        if(data == nullptr)
            this->memoryError();
        head = tail = 0;
    }
    
    ~ArrayQueue()
    {
        delete []data;
    }
    virtual bool isEmpty()
    {
        return head == tail;
    }

    virtual int size()
    {
        return (tail - head + capacity)%capacity;
    }

    virtual void push(T value)
    {
        if(size()+1 < capacity)
        {
            data[tail] = value;
            tail = (tail + 1)%capacity;
        }
        else
        {
            this->memoryError();
        }
    }

    virtual T pop()
    {
        if(isEmpty())
            this->emptyError();
        T temp = data[head];
        head = (head + 1)%capacity;
        return temp;
    }
};

#endif