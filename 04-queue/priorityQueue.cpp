#include <iostream>
#include "PriorityQueue.h"
using namespace std;
int main()
{
    Heap<double> heap;
    heap.insert(10);
    heap.printHeap();
    heap.insert(0);
    heap.printHeap();
    heap.insert(20);
    heap.printHeap();
    heap.insert(-10);
    heap.printHeap();
    for(int i = 30;i >= 11; --i)
        heap.insert(i);
    heap.printHeap();
    double popValue, *p = &popValue;
    for(int i = 0;i < 10; ++i)
    {
        heap.pop(p);
        heap.printHeap();
        cout << "*p = " << *p << endl;
    }
    int a[] = {1,2,3,-1,-5,-10,0,9,-8};
    Heap<int> intHeap(a, sizeof(a)/sizeof(int));
    intHeap.printHeap();
    intHeap.insert(-100);
    intHeap.printHeap();
    return 0;
}