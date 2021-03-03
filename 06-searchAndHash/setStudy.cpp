#include <iostream>
#include <set>      // 集合 底层红黑树实现
using namespace std;
int main()
{
    set<int> s;
    s.insert(10);
    s.insert(20);
    s.insert(30);
    for(auto &elem : s)
        cout << elem << " ";
    cout << endl;
    set<int> s2;
    s2.insert(40);
    s2.insert(s.begin(), s.end());  // 相当于并运算
    for(auto &elem : s2)
        cout << elem << " ";
    cout << endl;
    return 0;
}