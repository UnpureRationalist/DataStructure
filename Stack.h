#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

template <class T>
class Stack
{
private:
    T *bottom;
    int size;
    int capacity;

    void memoryError()
    {
        cerr << "Memory Error!\n";
        exit(-1);
    }

    void emptyError()
    {
        cerr << "Stack is empty!\n";
        exit(-1);
    }

public:
    Stack()
    {
        bottom = new T[capacity = 10];
        if (bottom == NULL)
            memoryError();
        size = 0;
    }
    ~Stack()
    {
        if (bottom != NULL)
            delete []bottom;
    }

    void push(T value)
    {
        if(size + 1 > capacity)
        {
            T *space = new T[capacity <<= 1];
            if(space == NULL)
                memoryError();
            memcpy(space, bottom, sizeof(T)*size);
            delete []bottom;
            bottom = space;
        }
        bottom[size] = value;
        size++;
    }

    T top()
    {
        if(size == 0)
            emptyError();
        return bottom[size - 1];
    }

    T pop()
    {
        if(size == 0)
            emptyError();
        size--;
        T value = bottom[size];
        if( capacity >= 20 && size < (capacity >> 1))
        {
            T *space = new T[capacity >>= 1];
            if(space == NULL)
                memoryError();
            memcpy(space, bottom, sizeof(T)*size);
            delete []bottom;
            bottom = space;
        }
        return value;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    int length()
    {
        return size;
    }
};