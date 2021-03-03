#ifndef SORT_ALGORITHM
#define SORT_ALGORITHM

#include <iostream>
#include <cmath>
#include "../04-queue/Queue.h"
using namespace std;

template <class T>
void printArray(const T *a, int length)
{
    for (int i = 0; i < length; ++i)
        cout << a[i] << '\t';
    cout << endl;
}

/*
*                  简单选择排序
* 核心思想：每次从未排序的元素中选择最⼩（⼤）的，放⼊已排序序列
* 时间复杂度： 最好 Θ(N)    最坏 Θ(N^2)   平均 Θ(N^2)
* 稳定性：  不稳定
*/
template <class T>
void simpleSelectionSort(T *a, int length)
{
    int mini;
    T minv;
    for (int i = 0; i < length - 1; ++i)
    {
        mini = i;
        minv = a[i]; // 初始化最小值和下标
        for (int j = i + 1; j < length; ++j)
        {
            if (a[j] < minv) // 寻找最小值
            {
                minv = a[j];
                mini = j;
            }
        }
        swap(a[i], a[mini]); // 交换
    }
}

/*
*                  简单插入排序
* 核心思想：每次把未排序的元素中第⼀个元素插⼊到已排序序列中
* 时间复杂度： 最好 Θ(N)    最坏 Θ(N^2)   平均 Θ(N^2)
* 稳定性：  稳定
*/
template <class T>
void simpleInsertionSort(T *a, int length)
{
    T value;
    for (int i = 1; i < length; ++i)
    {
        value = a[i];
        int j = i;
        for (; j > 0 && a[j - 1] > value; --j)
        {
            a[j] = a[j - 1];
        }
        a[j] = value;
    }
}

/*
*                  冒泡排序
* 核心思想：从序列起始位置两两⽐较，逆序则交换，到序列结束，谓之“⼀趟”
* 时间复杂度： 最好 Θ(N)    最坏 Θ(N^2)   平均 Θ(N^2)
* 稳定性：  稳定
*/
template <class T>
void bubbleSort(T *a, int length)
{
    bool sorted;
    for (int i = 0; i < length; ++i)
    {
        sorted = true;
        for (int j = 0; j < length - i - 1; ++j)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]); // 逆序则交换
                sorted = false;
            }
        }
        if (sorted) // 优化 使得最好情况下冒泡排序复杂的为 Θ(N)
            break;
    }
}

/*
*                 希尔排序
* 核心思想：变步长的插⼊排序
* 时间复杂度： Θ(N^k)  其中: 1 < k < 2  与步长的选取有关
* 稳定性：  不稳定
*/
template <class T>
void shellInsert(T *a, int length, int step) //分组进行插入排序
{
    for (int i = step; i < length; ++i)
    {
        if (a[i] <= a[i - step])
        {
            T temp = a[i];
            int j = i - step;
            for (; j >= 0 && temp <= a[j]; j -= step)
                a[j + step] = a[j];
            a[j + step] = temp;
        }
    }
}

template <class T>
void shellSort(T *a, int length)
{
    int stepArray[] = {5, 2, 1};
    /* 
    *  此步长序列需要根据待排序数组而定，此处仅是示例
	*  关于步长序列如何选取，可参考相关书籍或网上搜索相关内容 
    */
    int n = sizeof(stepArray) / sizeof(int);
    for (int i = 0; i < n; ++i)
        shellInsert(a, length, stepArray[i]);
}

/*
*                   堆排序
* 核心思想：利用堆的删除和调整操作，实现排序
* 时间复杂度： 最好 O(NlogN)    最坏 O(NlogN)   平均 O(NlogN)
* 稳定性：  不稳定
*/
template <class T>
void adjustHeap(T *a, int i, int length)
{
    T temp = a[i]; // 先取出当前元素i
    for (int k = i * 2 + 1; k < length; k = k * 2 + 1)
    {
        if (k + 1 < length && a[k] < a[k + 1]) // 从 i 结点的左子结点开始，也就是 2i+1 处开始
        {
            k++; // 如果左子结点小于右子结点，k指向右子结点
        }
        if (a[k] > temp)
        {
            a[i] = a[k]; // 如果子节点大于父节点，将子节点值赋给父节点（不用进行交换）
            i = k;
        }
        else
        {
            break;
        }
    }
    a[i] = temp; //将 temp 放到最终的位置
}

template <class T>
void heapSort(T *a, int length)
{
    // 首先建堆 从有孩子的节点开始调整
    for (int i = length / 2 - 1; i >= 0; --i)
    {
        adjustHeap(a, i, length);
    }
    // 调整堆结构 （ 交换堆顶元素与末尾元素 ）
    for (int i = length - 1; i > 0; --i)
    {
        swap(a[0], a[i]);    //将堆顶元素与末尾元素进行交换
        adjustHeap(a, 0, i); //重新对堆进行调整
    }
}

/*
*                   归并排序
* 核心思想：将两个已经有序序列合并 从而实现排序 分治
* 时间复杂度： 最好 Θ(NlogN)    最坏 Θ(NlogN)   平均 Θ(NlogN)
* 稳定性：  稳定
*/
template <class T>
void merge(T *a, T *temp, int leftIndex, int rightIndex, int rightEnd)
{
    int i = leftIndex;
    int leftEnd = rightIndex - 1, tempIndex = leftIndex;
    while (leftIndex <= leftEnd && rightIndex <= rightEnd)
    {
        if (a[leftIndex] <= a[rightIndex])
            temp[tempIndex++] = a[leftIndex++];
        else
            temp[tempIndex++] = a[rightIndex++];
    }
    while (leftIndex <= leftEnd)
        temp[tempIndex++] = a[leftIndex++];
    while (rightIndex <= rightEnd)
        temp[tempIndex++] = a[rightIndex++];
    for (; i <= rightEnd; ++i) // 拷贝回数组 a
        a[i] = temp[i];
}

template <class T>
void mSort(T *a, T *temp, int left, int right)
{
    if (left >= right)
        return;
    int mid = (left + right) / 2;
    mSort(a, temp, left, mid);
    mSort(a, temp, mid + 1, right);
    merge(a, temp, left, mid + 1, right);
}

template <class T>
void mergeSort(T *a, int length)
{
    T *temp = new (nothrow) T[length];
    if (temp == NULL)
        return;
    mSort(a, temp, 0, length - 1);
    delete[] temp;
}

/*
*                   快速排序
* 核心思想：分治 将某一元素（轴）移动到指定位置 大于、小于该元素的其它元素移到两侧 再对两侧进行同样操作
* 时间复杂度： 最好 Θ(NlogN)    最坏 Θ(N^2)   平均 Θ(NlogN)
* 稳定性：  不稳定
*/
template <class T>
T medianPivot(T *a, int left, int right)
{
    int mid = (left + right) / 2;
    if (a[left] > a[mid])
        swap(a[left], a[mid]);
    if (a[left] > a[right])
        swap(a[left], a[right]);
    if (a[mid] > a[right])
        swap(a[mid], a[right]);
    swap(a[mid], a[right - 1]);
    return a[right - 1];
}

const int cutoff = 3;

template <class T>
void qSort(T *a, int left, int right)
{
    if (right - left < cutoff)
    { // 小于指定元素数量 采用插入排序
        simpleInsertionSort(a + left, right - left + 1);
    }
    else
    {
        T pivot = medianPivot(a, left, right);
        int i = left, j = right - 1;
        while (1)
        {
            while (a[++i] < pivot)
                ;
            while (a[--j] > pivot)
                ; // 空语句
            if (i < j)
                swap(a[i], a[j]);
            else
                break;
        }
        swap(a[i], a[right - 1]);
        qSort(a, left, i - 1);
        qSort(a, i + 1, right); // 递归
    }
}

template <class T>
void quickSort(T *a, int length)
{
    qSort(a, 0, length - 1);
}

int getBit(unsigned int value, int bit) // 基数排序辅助函数 求value的第bit位数值 如123第3位数值为1
{
    int base = pow(10, bit - 1);
    return value / base % 10;
}
/*
*                基数排序
* 仅适用于 unsigned int 类型数组排序
*/
void radixSort(unsigned int *a, int length)
{
    unsigned int maxElem = a[0];
    for (int i = 1; i < length; ++i)
    {
        if (a[i] > maxElem)
            maxElem = a[i]; // 首先求最大值
    }
    Queue<unsigned int> q[10]; // 10（基数为10）个队列 用来模拟桶
    int bit = 1;               // 第 bit 位
    while (maxElem > 0)
    {
        if (bit == 1)
        { // 初始入队
            for (int i = 0; i < length; ++i)
            {
                q[getBit(a[i], bit)].push(a[i]);
            }
        }
        else
        {
            int sizeArray[10];
            for (int i = 0; i < 10; ++i)
                sizeArray[i] = q[i].size(); // 保存队列内元素数量大小
            for (int i = 0; i < 10; ++i)
            {
                int size = sizeArray[i];
                for (int j = 0; j < size; ++j)
                {
                    int value = q[i].pop();            // 出队
                    q[getBit(value, bit)].push(value); // 入队
                }
            }
        }
        maxElem /= 10; // 最大值除以 10  控制迭代次数
        ++bit;         // 位数加 1
    }
    int count = 0;
    for (int i = 0; i < 10; ++i)
    {
        while (!q[i].isEmpty())
        {
            a[count++] = q[i].pop(); // 将队列元素依次复制到原数组
        }
    }
}

#endif