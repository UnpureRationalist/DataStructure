#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

template <class T>
class ArrayList
{
private:
    T *a = NULL;
    int length;
    int capacity;

    void quickSort(int l, int r, bool(comp)(const T&, const T&))
    {
        if (l >= r)
            return;
        int i = l, j = r;
        T x = a[i];
        while (i < j)
        {
            while (i < j && !comp(a[j], x))
                j--;                        // 从右向左找第一个小于x的数
            if (i < j)
                a[i++] = a[j];
            while (i < j && comp(a[i], x))
                i++;                       // 从左向右找第一个大于x的数
            if (i < j)
                a[j--] = a[i];
        }
        a[i] = x;
        quickSort(l, i - 1, comp);
        quickSort(i + 1, r, comp);
    }

public:
    ArrayList()
    {
        a = new T[10];
        if (a == NULL)
        {
            cerr << "Memory Error!\n";
            exit(-1);
        }
        length = 0;
        capacity = 10;
    }

    ArrayList(T *p, int size)
    {
        a = new T[size + 10];
        if (a == NULL)
        {
            cerr << "Memory Error!\n";
            exit(-1);
        }
        length = size;
        capacity = size + 10;
        memcpy(a, p, sizeof(T) * size);
    }

    ArrayList(ArrayList<T> &tempList)
    {
        capacity = tempList.capacity;
        length = tempList.length;
        a = new T[capacity];
        if (a == NULL)
        {
            cerr << "Memory Error!\n";
            exit(-1);
        }
        memcpy(a, tempList.a, sizeof(T) * length);
    }

    ~ArrayList()
    {
        if (a != NULL)
            delete[] a;
    }

    //获取元素数量
    int getLength()
    {
        return length;
    }
    int getSize()
    {
        return length;
    }
    //获取容量
    int getCapacity()
    {
        return capacity;
    }

    //在位置k插入元素value
    bool insert(int k, T value)
    { //判断是否合法
        if (k > length || k < 0)
        {
            return false;
        }
        //若容量不够 重新申请内存
        if (length + 1 > capacity)
        {
            T *space = new T[capacity <<= 1];
            if (space == NULL)
                return false;
            memcpy(space, a, sizeof(T) * length);
            delete[] a;
            a = space;
        }
        int i = length;
        for (; i > k; --i)
        {
            a[i] = a[i - 1];
        }
        a[i] = value;
        length++;
        return true;
    }

    //删除位置 k 的元素 返回成功与否
    bool erase(int k)
    {
        if (k < 0 || k >= length)
            return false;
        else
        {
            int i = k + 1;
            for (; i < length; ++i)
                a[i - 1] = a[i];
            length--;
            //若数组长度过小 减小容量
            if (capacity > 10 && length < (capacity >> 1))
            {
                T *space = new T[capacity >>= 1];
                if (space == NULL)
                    return true;
                memcpy(space, a, sizeof(T) * length);
                delete[] a;
                a = space;
            }
            return true;
        }
    }

    //插入元素到最后
    bool push_back(T value)
    {
        return insert(length, value);
    }

    //插入元素到最前
    bool push_front(T value)
    {
        return insert(0, value);
    }

    //逆序
    void reverse()
    {
        int k = length >> 1;
        T temp;
        for (int i = 0; i < k; ++i)
        {
            temp = a[length - 1 - i];
            a[length - 1 - i] = a[i];
            a[i] = temp;
        }
    }

    //运算符重载 访问第i个元素
    T operator[](int k)
    {
        if (k < length && k >= 0)
            return a[k];
        else
        {
            cerr << "Index out of Boundary!\n";
            exit(-1);
        }
    }

    //排序 默认升序
    void sort()
    {
        quickSort(0,
                  length - 1,
                  [](const T& a, const T& b) -> bool { return a < b; });
    }

    //自定义排序规则
    void sort(bool(comp)(const T&, const T&))
    {
        quickSort(0, length - 1, comp);
    }

    //输出元素
    void printArray()
    {
        for (int i = 0; i < length; ++i)
        {
            cout << a[i] << " ";
        }
        cout << endl;
    }
};