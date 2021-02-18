#ifndef LGRAPH
#define LGRAPH

#include "Graph.h"

/*
    基于 邻接表 存储的图
*/
template<class T, class EdgeType>   // T 为顶点信息类型 EdgeType 为边距离类型
class LGraph : public Graph<T>
{
protected:
    vector<map<int, EdgeType>> adjL;

    void setAdjL()
    {
        adjL.resize(this->nv);
        for(auto &x : adjL)
            x.clear();
    }

    virtual void dfs(int v, void (*visit) (T &))
    {
        if(visit == NULL)
            cout << this->vertices[v] << "  ";  // 默认输出节点信息
        else
            visit(this->vertices[v]);           // 否则调用 visit 函数
        this->visited[v] = true;
        for(auto x : adjL[v])
        {
            if(!this->visited[x.first])
                dfs(x.first, visit);
        }
    }

public:
    LGraph(bool dir = false) : Graph<T>(dir) {   }

    LGraph(const vector<T> &v, bool dir = false) : Graph<T>(v, dir)
    {
        setAdjL();
    }

    LGraph(unsigned int numOfVertices, bool dir = false) : Graph<T>(numOfVertices, dir)
    {
        setAdjL();
    }

    void print()
    {
        for(int i = 0;i < this->nv; ++i)
        {
            cout << this->vertices[i] << "[" << i << "]-->";
            for(auto &x : adjL[i])
                cout << this->vertices[x.first] << "(" << x.second << ")  ";
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
        // 下面修改邻接表内容
        adjL.push_back(map<int, EdgeType>());
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
        if(adjL[src].find(dest) != adjL[src].end())
            return false;
        adjL[src].insert(pair<int, EdgeType>(dest, weight));
        if(!this->directed)    // 若为无向图
            adjL[dest].insert(pair<int, EdgeType>(src, weight));
        return true;
    }

    bool removeE(const T src, const T dest)
    {
        // return Graph<T>::removeE(this->iov[src], this->iov[dest]);
        if(this->iov.find(src) == this->iov.end() || this->iov.find(dest) == this->iov.end())
            return false;
        return removeE(this->iov[src], this->iov[dest]);
    }

    bool removeE(const int src, const int dest)
    {
        if(src<0 || dest<0 || src>= this->nv || dest>= this->nv)
            return false;
        if(adjL[src].find(dest) == adjL[src].end())
            return false;
        adjL[src].erase(dest);
        if(!this->directed)
            adjL[dest].erase(src);
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
            for( auto &x : adjL[w])
            {
                if(!this->visited[x.first])
                {
                    if(visit == NULL)       // 访问节点
                        cout << this->vertices[x.first] << "  ";
                    else
                        visit(this->vertices[x.first]);
                    this->visited[x.first] = true;
                    q.push(x.first);
                }
            }
        }
        if(visit == NULL)
            cout << endl;
    }

    bool topSort()      // 拓扑排序
    {
        if(!this->directed)     // 若不是有向图 返回 false
            return false;
        vector<int> inDegree(this->nv, 0);    // 存储入度
        for(auto v : adjL)
            for(auto w : v)
                ++inDegree[w.first];    // 计算入度
        queue<int> q;
        for(int i = 0;i < this->nv; ++i)
            if(inDegree[i] == 0)
                q.push(i);      // 入度为 0 顶点入队
        int count = 0, v;
        while(!q.empty())
        {
            v = q.front();
            q.pop();
            cout << this->vertices[v] << "  ";  // 输出
            ++count;
            for(auto w : adjL[v])
            {
                --inDegree[w.first];
                if(inDegree[w.first] == 0)
                    q.push(w.first);
            }
        }
        cout << endl;
        if(count != this->nv)
            return false;       // 输出点不够 说明有环 拓扑排序失败
        return true;
    }

    void shortest(const T src)
    {
        if(this->iov.find(src) == this->iov.end())
            return;
        vector<EdgeType> d(this->nv, maxEdgeWeight);
        d[this->iov[src]] = 0;      // 起点距离设置为 0
        queue<int> q;
        q.push(this->iov[src]);
        int v;
        while(!q.empty())
        {
            v = q.front();
            q.pop();
            for(auto w : adjL[v])
            {
                if(d[w.first] == maxEdgeWeight)
                {
                    d[w.first] = d[v] + 1;
                    q.push(w.first);
                }
            }
        }
        for(int i = 0;i < this->nv; ++i)
        {
            cout << this->vertices[i] << "(" << d[i] << ")  ";
        }
        cout << endl;
    }
};

#endif