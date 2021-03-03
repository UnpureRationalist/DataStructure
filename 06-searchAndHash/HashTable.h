#ifndef HASH_TABLE
#define HASH_TABLE
#include <iostream>
using namespace std;

enum GridStatus
{
    Active,  // 占用
    Removed, // 已删除
    Empty    // 空闲位置
};

template <class T>
class HashTable
{
private:
    T *data;
    GridStatus *status; // 该位置状态
    int size;           // 哈希表容量大小
    int remains;        // 剩余容量大小

    bool isPrime(int x) // 判断 x 是否为质数
    {
        if (x < 2)
            return false;
        if (x == 2)
            return true;
        if (x % 2 == 0)
            return false;
        for (int i = 3; i * i <= x; i+=2)
        {
            if (x % i == 0)
                return false;
        }
        return true;
    }

    int getPrime(int x) // 寻找大于等于 x 的最小质数 作为哈希表长度
    {
        for (int i = x; i > 0; ++i)
        {
            if (isPrime(i))
                return i;
        }
        return x;
    }

    void MemoryError()
    {
        cerr << "Memory Limit Exceeded!" << endl;
        exit(-1);
    }

    int hash(int value)
    {
        return value % size;
    }

public:
    HashTable(int s)
    {
        remains = size = getPrime(s);
        data = new (nothrow) T[size];
        if (data == NULL)
            MemoryError();
        status = new (nothrow) GridStatus[size];
        if (status == NULL)
        {
            delete[] data;
            MemoryError();
        }
        for (int i = 0; i < size; ++i)
            status[i] = Empty; // 初始化 status 数组
    }

    ~HashTable()
    {
        delete[] data;
        delete[] status;
    }

    bool isFull() const
    {
        return remains == 0;
    }

    bool insert(T value)
    {
        if (isFull())
            return false;
        int pos = hash(int(value)); // 此处采用模运算确定元素在哈希表中位置 需要定义 T 类型到 int 类型转换规则
        while (status[pos] == Active)
        {
            pos = (pos + 1) % size; // 此处采用线性探测法 也可采用平方探测等其他方法
        }
        data[pos] = value;
        status[pos] = Active;
        --remains;
        return true;
    }

    int find(T value)
    {
        int pos, index;
        pos = index = hash(int(value));
        while (status[pos] != Empty)
        {
            if (status[pos] == Active && data[pos] == value)
                return pos;
            pos = (pos + 1) % size;
            if (pos == index)
                break; // 循环一圈 退出循环
        }
        return -1;
    }

    bool remove(T value)
    {
        int pos = find(value); // 先查找元素位置
        if (pos == -1)
            return false;
        status[pos] = Removed; // 标记删除
        ++remains;             // 剩余数量加 1
        return true;
    }

    void print()
    {
        for (int i = 0; i < size; ++i)
            cout << i << "\t";
        cout << endl;
        for (int i = 0; i < size; ++i)
        {
            if (status[i] == Active)
                cout << data[i];
            else if (status[i] == Removed)
                cout << "--";
            else
                cout << "  ";
            cout << "\t";
        }
        cout << endl;
    }
};

#endif