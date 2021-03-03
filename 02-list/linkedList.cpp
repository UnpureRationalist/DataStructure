#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "LinkedList.h"
using namespace std;

int main()
{
    LinkedList<int> list;
    cout << "list.size()  = " << list.size() << endl;
    list.insert(1, 2);
    cout << "list.size()  = " << list.size() << endl;
    list.insert(1, 4);
    cout << "list.size()  = " << list.size() << endl;
    list.insert(3, 300);
    cout << "list.size()  = " << list.size() << endl;
    list.traverse();

    double array[] = {1.23, 4.56, -78, 123, 0, +123};
    LinkedList<double> doubleList(array, sizeof(array) / sizeof(double));
    doubleList.insert(1, 123456);
    doubleList.traverse();

    cout << "construct from list:\n";
    LinkedList<double> doubleList2(doubleList);
    doubleList2.traverse();

    cout << "construct from vector:\n";
    int intArray[] = {0, 1, 2, 4, 0, -9, 0, 30, 0, 30, -1};
    ArrayList<int> intVector(intArray, sizeof(intArray) / sizeof(int));
    LinkedList<int> list2(intVector);
    list2.traverse();

    cout << "before erase:\n";
    list2.traverse();
    list2.erase(1);
    cout << "after erase:\n";
    list2.traverse();

    cout << "find:\n";
    int *pint = list2.find(4);
    cout << "pint = " << pint << endl;
    if (pint != NULL)
        cout << " *pint = " << *pint << endl;

    cout << "bofore reverse:\n";
    list2.traverse();
    list2.reverse();
    cout << "after reverse:\n";
    list2.traverse();

    cout << "before sort(default):\n";
    list2.traverse();
    list2.sort();
    cout << "after sort(default):\n";
    list2.traverse();

    cout << "before sort(self define):\n";
    list2.traverse();
    list2.sort([](const int &a, const int &b) -> bool { return a > b; });
    cout << "after sort(self define):\n";
    list2.traverse();

    cout << "before remove 1:\n";
    list2.traverse();
    list2.remove(1);
    cout << "after remove 1:\n";
    list2.traverse();
    return 0;
}