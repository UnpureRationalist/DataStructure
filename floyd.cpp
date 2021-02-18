#include <iostream>
using namespace std;
// 动态规划 Floyd算法 解决多元最短路径问题
const int inf = 1000000; // 设置一个值作为无穷
const int maxNum = 10;
int n = 4; // 顶点数
int adjMatrix[maxNum][maxNum] = {
    {0, 5, inf, 7},
    {inf, 0, 4, 2},
    {3, 3, 0, 2},
    {inf, inf, 1, 0}};    // 原始邻接矩阵
int d[maxNum][maxNum];    // 保存最小路径值
int path[maxNum][maxNum]; // 保存最小路径走法

void getPath(int i, int j) // 输出从 i 到 j 的路径
{
    if (path[i][j] == -1 || d[i][j] == adjMatrix[i][j])
    {
        cout << i << " -> " << j;
        return;
    }
    getPath(i, path[i][j]); // 递归
    cout << " -> " << j;
}

void floyd()
{
    // 首先初始化 d 数组和 path 数组
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            d[i][j] = adjMatrix[i][j];
            if (i != j && adjMatrix[i][j] < inf) // 非对角线以及非无边连接的
                path[i][j] = i;
            else
                path[i][j] = -1;
        }
    }
    // 依次插入中间点
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (d[i][k] + d[k][j] < d[i][j]) // 更新最小路径
                {                                // 注意：d[i][k] + d[k][j] 计算可能发生溢出 不能将 inf 赋值为 INT_MAX
                    d[i][j] = d[i][k] + d[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
    // 输出
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i != j)
            {
                cout << "d[" << i << "][" << j << "] = " << d[i][j] << "\t";
                cout << "path:\t";
                getPath(i, j);
                cout << endl;
            }
        }
        cout << endl;
    }
}
int main()
{
    floyd();
    return 0;
}