#include <iostream>
#include "LinkedlistQueue.h"
#include "ArrayQueue.h"
using namespace std;

int main()
{
    
    LinkedlistQueue<int> intQueue;
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
    LinkedlistQueue<double> doubleQueue(array, length);
    while (!doubleQueue.isEmpty())
    {
        cout << "doubleQueue.size() = " << doubleQueue.size() << endl;
        cout << "doubleQueue.pop() = " << doubleQueue.pop() << endl;
    }
    
    int n = 5;
    ArrayQueue<int> q(n);
    for (int i = 0; i < n; ++i)
    {
        q.push(i);
        cout << "size = " << q.size() << endl;
    }
    cout << q.size() << endl;
    while (!q.isEmpty())
        cout << q.pop() << "\t";
    cout << endl;

    for (int i = 0; i < n/2; ++i)
    {
        q.push(i*i);
        cout << "size = " << q.size() << endl;
    }

    while (!q.isEmpty())
        cout << q.pop() << "\t";
    cout << endl;

    for (int i = 0; i < n; ++i)
    {
        q.push(i*i*i);
        cout << "size = " << q.size() << endl;
    }
    while (!q.isEmpty())
        cout << q.pop() << "\t";
    cout << endl;
    return 0;
}