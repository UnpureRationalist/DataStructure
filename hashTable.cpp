#include <iostream>
#include "HashTable.h"
using namespace std;
int main()
{
    HashTable<int> h(11);
    h.insert(10);
    h.insert(5);
    h.insert(16);
    h.insert(21);
    h.insert(33);
    h.print();
    cout << h.find(10) << endl;
    cout << h.find(33) << endl;
    cout << h.find(1) << endl;
    h.insert(9);
    h.remove(10);
    h.print();
    cout << h.find(21) << endl;
    return 0;
}