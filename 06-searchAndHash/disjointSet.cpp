#include <algorithm>
#include "DisjointSet.h"
using namespace std;

int main()
{
    DisjointSet<int> s(20);
    s.insert(11);
    s.insert(22);
    s.insert(66);
    s.insert(-5);
    s.insert(123);
    cout << "s.size() = " << s.getSize() << endl;
    cout << "s.capacity() = " << s.getCapacity() << endl;
    cout << s.find(8) << endl;
    s.unionSet(11, 66);
    s.unionSet(11, 22);
    s.unionSet(123, -5);
    s.unionSet(123, 11);
    s.find(123);
    s.print();
    return 0;
}