#include <iostream>
#include <cmath>
using namespace std;
// 回溯
int N = 8;
int queens[50];
int countSolution = 0;
bool legal(int k, int i)  // k 号皇后能否放在第 i 位置
{
    for(int j = 0; j < k; ++j)
    {
        if(queens[j] == i || abs(queens[j]-i) == abs(j-k))
            return false;   // 同一列或者同一对角线 不可以放
    }
    return true;
}
void place(int k)   // 放第 N 个皇后
{
    if(k == N)
    {   // 输出
        ++countSolution;
        cout << countSolution << ":\t";
        for(int i = 0;i < N; ++i)
            cout << queens[i]+1 << " ";
        cout << endl;
        return;
    }
    for(int i = 0;i < N; ++i)
    {
        if(legal(k, i))
        {
            queens[k] = i;
            place(k+1);
        }
    }
}
int main()
{
    cin >> N;
    place(0);
    return 0;
}