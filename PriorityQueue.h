#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE
/*
* 用堆实现优先队列
* 堆是一个几乎完全的二叉树
* 本代码以 小顶堆 为例实现
*/
#include <iostream>
#include <cstring>
using namespace std;

template<class T>
class Heap
{
    private:
        T *data;
        int size;
        int capacity;

        void MemoryError()
        {
            cerr << "Memory Limit Exceeded!" << endl;
            exit(-1);
        }

        // 元素上移
        void ShitUp(int k)
        {
            T x = data[k];
            int i = k;
            for( ; i>1 && x<data[i/2]; i /= 2)
            {
                data[i] = data[i/2];
            }
            data[i] = x;
        }

        // 元素下移
        void ShitDown(int k)
        {
            T x = data[k];
            int i = k, child;
            for( ; i*2 <= size; i = child)   // 有儿子
            {
                child = i*2;
                if(child != size && data[child] > data[child+1])
                    ++child;
                if(x > data[child])
                    data[i] = data[child];  // 向上移动
                else
                    break;
            }
            data[i] = x;
        }

    public:
        Heap(int maxSize)
        {
            if(maxSize <= 0)
            {
                cerr << "Parameter Error!" << endl;
                exit(-1);
            }
            data = new T[maxSize+1];    // 数组 0 号位置不存元素
            if(data == NULL)
            {
                MemoryError();
            }
            size = 0;
            capacity = maxSize;
        }

        Heap()
        {
            data = new T[9];
            if(data == NULL)
            {
                MemoryError();
            }
            size = 0;
            capacity = 8;
        }

        Heap(const T *a, int length)
        {
            data = new T[length+1];
            if(data == NULL)
                MemoryError();
            memcpy(data+1, a, sizeof(T)*length);
            size = length;
            capacity = length;
            for(int i = length/2; i > 0; --i)
            {
                ShitDown(i);
            }
        }

        ~Heap()
        {
            if(data)
                delete []data;
        }

        // 打印堆
        void printHeap()
        {
            for(int i = 1; i <= size; ++i)
            {
                cout << data[i] << " ";
            }
            cout << endl;
        }

        // 插入
        bool insert(T value)
        {
            // 判断容量是否够
            if(size == capacity)
            {
                T *temp = new T[(capacity << 1) + 1];
                if(temp == NULL)
                {
                    cerr << "Memory Limit Exceeded!" << endl;
                    return false;
                }
                memcpy(temp, data, sizeof(T)*(capacity+1));
                delete []data;
                data = temp;
                capacity <<= 1;
            }
            data[++size] = value;   // 实际上元素数量过多可能使 size 或者 capacity 溢出 此处未考虑
            ShitUp(size);
            return true;
        }

        // 删除
        bool pop(T *p)
        {
            if(size == 0)
                return false;
            *p = data[1];   // 保存弹出的元素
            data[1] = data[size--];
            ShitDown(1);
            return true;
        }

        bool empty()
        {
            return size == 0;
        }

        int getSize()
        {
            return size;
        }

        int getCapacity()
        {
            return capacity;
        }
};

#endif