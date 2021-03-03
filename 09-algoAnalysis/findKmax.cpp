#include <iostream>
#include <algorithm>
using namespace std;
// 分治
void findKmax(int *a, int left, int right, int k)
{
    int i = left,  j = right, partition = a[i];
    while(i != j)
    {
        while (i<j && a[j]>=partition)
            --j;
        swap(a[i], a[j]);
        while (i<j && a[i]<partition)
            ++i;
        swap(a[i], a[j]);
    }
    if(right-i+1 == k)
        return;
    else if(right-i+1 > k)
        findKmax(a, i+1, right, k);
    else
        findKmax(a, left, i-1, k-(right-i+1));
}
int findKmax(int *a, int length, int k)
{
    findKmax(a, 0, length-1, k);
    return a[length-k];
}
int main()
{
    int a[100];
    for(int i = 0;i < 100; ++i)
        a[i] = i+1;
    for(int i = 1;i <= 10; ++i)
    {
        random_shuffle(begin(a), end(a));
        cout << findKmax(a, sizeof(a)/sizeof(int), i) << endl;
    }
    return 0;
}

/*
                求第K个大的数

[整体思路]
    利用递归，将大的数字向右放置，然后取出第K个大的数。

[详细步骤]
    1.声明一个数组，长度为n，并给数组赋值
    2.定义函数findKmax,将最大值向右放置
        a)如果右侧部分大小==k，则递归结束
        b)如果右侧部分大小>k，则继续在基准值右侧寻找
        c)如果右侧部分大小<k，则在基准值左侧寻找
    3.递归结束之后，输出数组中第n-k位的值

*/