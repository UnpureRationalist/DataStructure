#ifndef DISJOINT_SET
#define DISJOINT_SET
#include <iostream>
#include <map>
using namespace std;

template <class T>
class DisjointSet
{
private:
    int *parent;   // 父节点下标
    T *data;       // 数据
    int capacity;  // 容量
    int size;      // 大小
    map<T, int> m; // 用于快速根据值查找下标

    void MemoryError()
    {
        cerr << "Memory Limit Exceeeded!" << endl;
        exit(-1);
    }

public:
    DisjointSet(int maxNum = 10) // 根据最大容量构造
    {
        capacity = maxNum;
        size = 0;
        parent = new (nothrow) int[maxNum + 1]; // 从下标 1 开始存储
        if (parent == NULL)
            MemoryError();
        data = new (nothrow) T[maxNum + 1];
        if (data == NULL)
            MemoryError();
    }

    ~DisjointSet()
    {
        delete[] parent;
        delete[] data;
    }

    bool insert(const T &value)
    {
        if (size == capacity)
            return false;
        data[++size] = value;
        m[value] = size; // 记录 值-下标 映射关系
        parent[size] = -1;
        return true;
    }

    void print() const
    { // 三行 分别打印下标、父节点位置、元素值
        cout << "index:\t";
        for (int i = 1; i <= size; ++i)
            cout << i << "\t";
        cout << endl;
        cout << "parent:\t";
        for (int i = 1; i <= size; ++i)
            cout << parent[i] << "\t";
        cout << endl;
        cout << "value:\t";
        for (int i = 1; i <= size; ++i)
            cout << data[i] << "\t";
        cout << endl;
    }

    // 查
    int find(T value) // 根据元素值查找 返回下标 -1 代表查找失败
    {
        auto it = m.find(value); // 返回迭代器
        if (it == m.end())
            return -1;
        int rt = it->second;
        while (parent[rt] > 0)
            rt = parent[rt]; // 迭代查找树根
        int temp;
        for (int i = it->second; i != rt; i = temp)
        {
            temp = parent[i];
            parent[i] = rt; // 路径压缩
        }
        return rt;
    }

    // 并 根据元素值，进行并操作
    void unionSet(T x, T y)
    {
        int rx = find(x), ry = find(y);
        if (rx == -1 || ry == -1)
            return; // 若有一个查找失败 直接返回
        if (rx == ry)
            return; // 同一个集合不需要合并
        if (parent[rx] < parent[ry])
        {
            parent[rx] += parent[ry];
            parent[ry] = rx;
        }
        else
        {
            parent[ry] += parent[rx];
            parent[rx] = ry;
        }
    }

    int getSize() const
    {
        return size;
    }

    int getCapacity() const
    {
        return capacity;
    }
};

#endif