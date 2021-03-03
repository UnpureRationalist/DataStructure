#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "Vector.h"
using namespace std;

struct myNode
{
    double sum;
    int id;

    myNode() {}
    myNode(double sum, double id)
    {
        this->sum = sum;
        this->id = id;
    }

    bool operator<(const myNode &temp) const
    {
        if (sum != temp.sum)
            return sum < temp.sum;
        else
            return id < temp.id;
    }

    friend ostream &operator<<(ostream &o, const myNode &temp);
};

ostream &operator<<(ostream &o, const myNode &temp)
{
    o << "[sum = " << temp.sum << ",id = " << temp.id << "]";
    return o;
}

int main()
{
    int array[] = {1, 4, -9, 0, 30};
    ArrayList<int> list(array, sizeof(array) / sizeof(int));
    for (int i = 0; i < 15; ++i)
    {
        list.insert(0, i + 1);
    }
    list.printArray();
    list.erase(list.getSize() - 1);
    list.printArray();
    cout << "list.getCapacity() = " << list.getCapacity() << endl;
    for (int i = 0; i < 12; ++i)
    {
        list.push_back(i);
        cout << "list.getCapacity() = " << list.getCapacity() << endl;
        if (i % 10 == 0)
            list.printArray();
    }
    list.printArray();
    ArrayList<int> copy(list);
    copy.printArray();
    copy.reverse();
    copy.printArray();
    cout << "copy[0] = " << copy[0] << endl;
    copy.sort();
    copy.printArray();
    /*
        参考:  
            C++ 11 Lambda表达式:
            https://blog.csdn.net/lcalqf/article/details/79401210
    */
    list.sort([](const int &a, const int &b) -> bool { return a > b; });
    list.printArray();
    list.sort();
    list.printArray();

    //结构体向量 需自定义运算符重载
    ArrayList<myNode> nodeLists;
    nodeLists.push_front(myNode(12.34, 5));
    nodeLists.insert(0, myNode(12.34, 3));
    nodeLists.insert(0, myNode(-12.34, 0));
    nodeLists.insert(0, myNode(129.34, 6));
    nodeLists.insert(0, myNode(-1265.34, -5));
    nodeLists.printArray();
    nodeLists.sort();
    nodeLists.printArray();
    return 0;
}