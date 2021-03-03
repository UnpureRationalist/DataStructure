#include <iostream>
using namespace std;
/*
    回溯 求全排列
*/
int n = 4;
const int MAX = 100;
int a[MAX];
bool flag[MAX + 1] = {0};
void fact(int k)
{
    if (k == n)
    {
        for (int i = 0; i < n; ++i)
            cout << a[i] << "\t";
        cout << endl;
        return;
    }
    for (int i = 1; i <= n; ++i)
    {
        if (!flag[i])
        {
            a[k] = i;
            flag[i] = true;
            fact(k + 1);     // 递归
            flag[i] = false; // 回溯
        }
    }
}
int main()
{
    fact(0);
    return 0;
}