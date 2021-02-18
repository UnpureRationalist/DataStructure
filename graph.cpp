#include <iostream>
#include <string>
#include <queue>
#include "MGraph.h"
#include "LGraph.h"
#include "DisjointSet.h"
using namespace std;
void myVisit(string &nodeInfo)
{
    nodeInfo += nodeInfo;
}
struct Edge
{
    string u;
    string v;
    int weight;

    Edge(string u,string v,int weight) : u(u), v(v), weight(weight)    {   }

    Edge() {}

    bool operator < (const Edge &e) const
    {
        return this->weight > e.weight; // 建小顶堆
    }
};

int main()
{
    /*
    vector<string> v{"AA", "BB", "CC", "DD", "EE"};
    LGraph<string, int> g(v);
    g.insertV("XX");
    g.insertE("AA", "CC");
    g.insertE(1, 3);
    g.insertE(1, 4);
    g.insertE(1, 0);
    g.insertE(2, 3);
    g.insertE("DD", "EE", 6);
    g.insertE("X", "EE");
    g.insertE("P", "Q", 102);
    g.removeE("P", "Q");
    cout << g.findE("P") << endl;
    cout << g.findE("A") << endl;
    */
    // g.removeE(1, 3);
    // g.insertV();
    // g.print();
    // g.dfs("AA", myVisit);
    // g.dfs("CC");
    // g.dfs("BB");
    // g.bfs("CC", myVisit);
    /*

5
C03 C04
C04 C05
C01 C02
C05 C06
C02 C06

    */
    /* 拓扑排序测试
   int n;
   cin >> n;
   string s1,s2;
   LGraph<string, int> g(true);
   for(int i = 0;i < n; ++i)
   {
       cin >> s1 >> s2;
       g.insertE(s1, s2);
   }
   g.topSort();
   */
    // g.bfs("CC");
    /* 无权图最短路径测试
12
A B
C A
A D
B D
B E
D C
D E
C F
D F
D G
E G
G F


    int n;
    cin >> n;
    string s1, s2;
    LGraph<string, int> g(true);    // 有向图
    for (int i = 0; i < n; ++i)
    {
        cin >> s1 >> s2;
        g.insertE(s1, s2);
    }
    g.print();
    g.shortest("C");
*/
/*
Dijkstra算法测试
12
A B 2
C A 4
A D 1
B D 3
B E 10
D C 2
D E 2
C F 5
D F 8
D G 4
E G 6
G F 1

*/
/*
    MGraph<string, int> g(true);    // 有向图
    int n;
    cin >> n;
    string s1, s2;
    int weight;
    for (int i = 0; i < n; ++i)
    {
        cin >> s1 >> s2 >> weight;
        g.insertE(s1, s2, weight);
    }
*/
    // g.dijkstra("A");
/*
weightedShortest测试

12
A B 2
C A 4
A D 1
B D -2
B E 10
D C 2
D E 2
C F 5
D F 8
D G 4
E G 6
G F 1

*/
/*
Prim算法测试数据

12
A B 2
C A 4
A D 1
B D 3
B E 10
D C 2
D E 7
C F 5
D F 8
D G 4
E G 6
G F 1


*/
/*
    MGraph<string, int> g;    // 无向图
    int n;
    cin >> n;
    string s1, s2;
    int weight;
    for (int i = 0; i < n; ++i)
    {
        cin >> s1 >> s2 >> weight;
        g.insertE(s1, s2, weight);
    }
    // g.weightedShortest("A");
    g.prim("A");
*/

/*
Kruskal 算法测试数据  适合稀疏图

7
A B C D E F G
12
A B 2
C A 4
A D 1
B D 3
B E 10
D C 2
D E 7
C F 5
D F 8
D G 4
E G 6
G F 1


*/
    // Kruskal 算法测试
    priority_queue<Edge> q;
    vector<Edge> edges;
    int nv, ne, w;      // 顶点数 边数 权重
    cin >> nv;
    DisjointSet<string> ds(nv);
    string u, v;
    for(int i = 0;i < nv; ++i)
    {
        cin >> u;
        ds.insert(u);
    }
    cin >> ne;
    for(int i = 0;i < ne; ++i)
    {
        cin >> u >> v >> w;
        q.emplace(u, v, w);
    }
    int countEdges = 0, minCost = 0;
    Edge e;
    while (countEdges < nv-1 && !q.empty())
    {
        e = q.top();
        q.pop();
        if(ds.find(e.u) != ds.find(e.v))
        {
            ds.unionSet(e.u, e.v);
            edges.push_back(e);
            minCost += e.weight;
            ++countEdges;
        }
    }
    if(countEdges != nv-1)      // 不存在生成树
        cout << "Error: Only " << countEdges << " edges found!" << endl;
    else
    {
        cout << minCost << endl;
        for(auto x : edges)
            cout << x.u << "," << x.v << "(" << x.weight << ")" << endl;
    }
    return 0;
}