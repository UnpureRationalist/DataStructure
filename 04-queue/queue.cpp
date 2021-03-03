#include <iostream>
#include "Queue.h"
using namespace std;

int main()
{
    Queue<int> intQueue;
    cout << "intQueue.isEmpty() = " << intQueue.isEmpty() << endl;
    cout << "intQueue.size() = " << intQueue.size() << endl;
    for(int i = 0;i < 50; ++i)
    {
        intQueue.push(i);
    }
    cout << "intQueue.size() = " << intQueue.size() << endl;
    for(int i = 0;i < 5; ++i)
    {
        cout << "intQueue.pop() = " << intQueue.pop() << endl;
    }
    cout << "intQueue.size() = " << intQueue.size() << endl;
    double array[] = {-123.45, 6.7, +8.9, -0.123, 1e4};
    int length = sizeof(array)/sizeof(double);
    Queue<double> doubleQueue(array, length);
    while (!doubleQueue.isEmpty())
    {
        cout << "doubleQueue.size() = " << doubleQueue.size() << endl;
        cout << "doubleQueue.pop() = " << doubleQueue.pop() << endl;
    }
    return 0;
}