#include <iostream>
#include <algorithm>
#include <string>
#include "SortAlgorithm.h"
using namespace std;

int main()
{
    double array[] = {-23.4, 12, -9, 0.5, 123, 0, 666, -234, -454.6};
    int length = sizeof(array) / sizeof(double);
    string before = "Before sort:\n", after = "After sort:\n";
    cout << before;
    printArray(array, length);
    simpleSelectionSort(array, length);     // 简单选择排序
    cout << after;
    printArray(array, length);

    random_shuffle(begin(array), end(array));   // 随机排列数组 包含在 algorithm 头文件中
    cout << endl << before;
    printArray(array, length);
    simpleInsertionSort(array, length);     // 简单插入排序
    cout << after;
    printArray(array, length);

    random_shuffle(begin(array), end(array));   // 随机排列数组
    cout << endl << before;
    printArray(array, length);
    bubbleSort(array, length);              // 冒泡排序
    cout << after;
    printArray(array, length);


    random_shuffle(begin(array), end(array));
    cout << endl << before;
    printArray(array, length);
    shellSort(array, length);               // 希尔排序
    cout << after;
    printArray(array, length);

    random_shuffle(begin(array), end(array));
    cout << endl << before;
    printArray(array, length);
    heapSort(array, length);                // 堆排序
    cout << after;
    printArray(array, length);

    random_shuffle(begin(array), end(array));
    cout << endl << before;
    printArray(array, length);
    mergeSort(array, length);               // 归并排序
    cout << after;
    printArray(array, length);

    random_shuffle(begin(array), end(array));
    cout << endl << before;
    printArray(array, length);
    quickSort(array, length);               // 快速排序
    cout << after;
    printArray(array, length);


    unsigned int a[] = {1200, 15, 15, 15, 234, 567, 666, 0, 777, 88, 99, 145, 252, 23, 3, 1234, 1234234};
    int size = sizeof(a) / sizeof(int);
    cout << endl << before;
    printArray(a, size);
    radixSort(a, size);                     // 基数排序
    cout << after;
    printArray(a, size);
    return 0;
}