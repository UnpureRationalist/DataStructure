#ifndef MGRAPH
#define MGRAPH
#include "Graph.h"

/*
    基于 邻接矩阵 存储的图
*/
template<class T, class EdgeType>   // T 为顶点信息类型 EdgeType 为边距离类型
class MGraph : public Graph<T>
{
protected:
    vector<vector<EdgeType>> adjM;  // 邻接矩阵

    void setAdjM()      // 设置邻接矩阵
    {
        adjM.resize(this->nv);
        for(int i = 0;i < this->nv; ++i)
        {
            adjM[i].resize(this->nv);
            for(int j = 0;j < this->nv; ++j)
            {
                adjM[i][j] = maxEdgeWeight;     // 初始化为 int 类型最大值
            }
        }
    }

    virtual void dfs(int v, void (*visit) (T &))
    {
        if(visit == NULL)
            cout << this->vertices[v] << "  ";  // 默认输出节点信息
        else
            visit(this->vertices[v]);           // 否则调用 visit 函数
        this->visited[v] = true;
        for(int j = 0;j < this->nv; ++j)
        {
            if(!this->visited[j] && adjM[v][j] != maxEdgeWeight)
                dfs(j, visit);
        }
    }

public:
    MGraph(bool dir = false) : Graph<T>(dir) {   }

    MGraph(const vector<T> &v, bool dir = false) : Graph<T>(v, dir)
    {
        setAdjM();
    }

    MGraph(unsigned int numOfVertices, bool dir = false) : Graph<T>(numOfVertices, dir)
    {
        setAdjM();
    }

    void print()
    {
        cout << '\t';
        for(int i = 0;i < this->nv; ++i)
            cout << this->vertices[i] << '\t';
        cout << endl;

        for(int i = 0;i < this->nv; ++i)
        {
            cout << this->vertices[i] <<":\t";
            for(int j = 0;j < this->nv; ++j)
            {
                if(adjM[i][j] == maxEdgeWeight)
                    cout << "-\t";
                else
                    cout << adjM[i][j] << '\t';
            }
            cout << endl;
        }
    }

    virtual void insertV()
    {
        insertV(to_string(this->nv));
    }

    virtual bool insertV(const T nodeInfo)
    {
        bool r = Graph<T>::insertV(nodeInfo);
        if(!r)
            return false;
        // 下面修改邻接矩阵内容
        for(int i = 0;i < this->nv - 1; ++i)
        {
            adjM[i].push_back(maxEdgeWeight);
        }
        adjM.push_back( vector<EdgeType>(this->nv, maxEdgeWeight) );
        return true;
    }

    virtual bool insertE(const T src, const T dest, EdgeType weight=1)   // 允许插入新顶点
    {
        insertV(src);
        insertV(dest);
        return insertE(this->iov[src], this->iov[dest], weight);
    }

    virtual bool insertE(const int src, const int dest, EdgeType weight=1)   // 不允许插入新顶点
    {
        if(src<0 || dest<0 || src>= this->nv || dest>= this->nv)
            return false;
        if(adjM[src][dest] != maxEdgeWeight)
            return false;
        adjM[src][dest] = weight;
        if(!this->directed)    // 若为无向图
            adjM[dest][src] = weight;
        return true;
    }

    bool removeE(const T src, const T dest)
    {
        // return Graph<T>::removeE(this->iov[src], this->iov[dest]);   // 编译报错？
        if(this->iov.find(src) == this->iov.end() || this->iov.find(dest) == this->iov.end())
            return false;
        return removeE(this->iov[src], this->iov[dest]);
    }

    bool removeE(const int src, const int dest)
    {
        if(src<0 || dest<0 || src>= this->nv || dest>= this->nv)
            return false;
        if(adjM[src][dest] == maxEdgeWeight)
            return false;
        adjM[src][dest] = maxEdgeWeight;
        if(!this->directed)
            adjM[dest][src] = maxEdgeWeight;
        return true;
    }

    virtual void dfs(const T &nodeInfo)
    {
        Graph<T>::dfs(nodeInfo);
    }

    virtual void dfs(const T &nodeInfo, void (*visit) (T &))
    {
        Graph<T>::dfs(nodeInfo, visit);
    }

    virtual void bfs(const T &nodeInfo)
    {
        bfs(nodeInfo, NULL);
    }

    virtual void bfs(const T &nodeInfo, void (*visit) (T &))     // 广度优先搜索
    {
        if(this->iov.find(nodeInfo) == this->iov.end())
            return;
        int index = this->iov[nodeInfo];
        this->visited.resize(this->nv);
        for(int i = 0;i < this->nv; ++i)
            this->visited[i] = false;      // 设置为未访问过
        queue<int> q;
        if(visit == NULL)   // 访问节点
            cout << this->vertices[index] << "  ";
        else
            visit(this->vertices[index]);
        this->visited[index] = true;
        q.push(index);
        int w;
        while(!q.empty())
        {
            w = q.front();  // 获取队首元素
            q.pop();        // 出队
            for(int i = 0;i < this->nv; ++i)
            {
                if(!this->visited[i] && adjM[w][i] != maxEdgeWeight)
                {
                    if(visit == NULL)       // 访问节点
                        cout << this->vertices[i] << "  ";
                    else
                        visit(this->vertices[i]);
                    this->visited[i] = true;
                    q.push(i);
                }
            }
        }
        if(visit == NULL)
            cout << endl;
    }

    void dijkstra(const T &src)
    {
        if(this->iov.find(src) == this->iov.end())
            return;
        vector<EdgeType> d(this->nv, maxEdgeWeight);    // 保存最小路径值
        vector<int> from(this->nv, -1);     // 记录最小路径走法
        vector<bool> known(this->nv, false);    // 记录是否已经计算得到最小路径
        d[this->iov[src]] = 0;
        EdgeType minDis;    // 最小值
        int v;              // 最小值对应编号
        for(int t = 0; t < this->nv; ++t)
        {
            minDis = maxEdgeWeight;
            v = -1;
            for(int i = 0;i < this->nv; ++i)
            {
                if( !known[i] && d[i] < minDis)
                {
                    minDis = d[i];
                    v = i;
                }
            }
            if(v == -1)
                break;      // 若不连通 跳出循环
            known[v] = true;
            for(int i = 0;i < this->nv; ++i)
            {
                if(adjM[v][i] != maxEdgeWeight && !known[i] && d[v]+adjM[v][i] < d[i])
                {
                    d[i] = d[v] + adjM[v][i];
                    from[i] = v;
                }
            }
        }
        // 输出
        for(int i = 0;i < this->nv; ++i)
            cout << i << '\t';
        cout << endl;
        for(int i = 0;i < this->nv; ++i)
            cout << this->vertices[i] << '\t';
        cout << endl;
        for(int i = 0;i < this->nv; ++i)
            cout << d[i] << '\t';
        cout << endl;
        for(int i = 0;i < this->nv; ++i)
            cout << (from[i]>=0 ? this->vertices[from[i]] : "-") << '\t';
        cout << endl;
    }

    void weightedShortest(const T &src)     // 带负权重边的最短路径算法（不能处理负回路）
    {
        if(this->iov.find(src) == this->iov.end())
            return;
        vector<EdgeType> d(this->nv, maxEdgeWeight);    // 保存最小路径值
        vector<int> from(this->nv, -1);     // 记录最小路径走法
        queue<int> q;
        vector<bool> inqueue(this->nv, false);
        d[this->iov[src]] = 0;
        q.push(this->iov[src]);
        inqueue[this->iov[src]] = true;     // 入队
        int v;
        while (!q.empty())
        {
            v = q.front();
            q.pop();
            inqueue[v] = false;
            for(int w = 0;w < this->nv; ++w)
            {
                if(adjM[v][w] != maxEdgeWeight && d[v]+adjM[v][w] < d[w])
                {
                    d[w] = d[v] + adjM[v][w];
                    from[w] = v;
                    if(!inqueue[w])
                    {
                        q.push(w);
                        inqueue[w] = true;  // 入队
                    }
                }
            }
        }
        // 输出
        for(int i = 0;i < this->nv; ++i)
            cout << i << '\t';
        cout << endl;
        for(int i = 0;i < this->nv; ++i)
            cout << this->vertices[i] << '\t';
        cout << endl;
        for(int i = 0;i < this->nv; ++i)
            cout << d[i] << '\t';
        cout << endl;
        for(int i = 0;i < this->nv; ++i)
            cout << (from[i]>=0 ? this->vertices[from[i]] : "-") << '\t';
        cout << endl;
    }

    void prim(const T &src)     // 最小生成树 适合稠密图
    {
        if(this->iov.find(src) == this->iov.end())
            return;
        vector<EdgeType> d(this->nv, maxEdgeWeight);    // 保存最小路径值
        vector<int> from(this->nv, -1);     // 记录最小路径走法
        vector<bool> known(this->nv, false);    // 记录是否已经加入生成树
        d[this->iov[src]] = 0;
        EdgeType minDis;    // 最小值
        int v;              // 最小值对应编号
        for(int t = 0; t < this->nv; ++t)
        {
            minDis = maxEdgeWeight;
            v = -1;
            for(int i = 0;i < this->nv; ++i)
            {
                if( !known[i] && d[i] < minDis)
                {
                    minDis = d[i];
                    v = i;
                }
            }
            if(v == -1)
                break;      // 若不连通 跳出循环
            known[v] = true;
            for(int i = 0;i < this->nv; ++i)
            {
                if(adjM[v][i] != maxEdgeWeight && !known[i] && adjM[v][i] < d[i])
                {
                    d[i] = adjM[v][i];
                    from[i] = v;
                }
            }
        }
        // 输出
        for(int i = 0;i < this->nv; ++i)
            cout << i << '\t';
        cout << endl;
        for(int i = 0;i < this->nv; ++i)
            cout << this->vertices[i] << '\t';
        cout << endl;
        for(int i = 0;i < this->nv; ++i)
            cout << d[i] << '\t';
        cout << endl;
        for(int i = 0;i < this->nv; ++i)
            cout << (from[i]>=0 ? this->vertices[from[i]] : "-") << '\t';
        cout << endl;
    }
};

#endif