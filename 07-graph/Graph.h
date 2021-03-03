#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;
const int maxEdgeWeight = INT_MAX;

template<class T>
class Graph
{
protected:
    unsigned int nv;    // 顶点数量
    bool directed;      // 是否为有向图
    vector<T> vertices; // 保存顶点信息
    map<T, int> iov;    // 便于快速根据顶点值查找顶点下标
    vector<bool> visited;   // 标记节点是否访问过

    virtual void dfs(int v, void (*visit) (T &)) = 0;

public:
    Graph(bool dir = false)
    {
        directed = dir;
        nv = 0;
    }

    Graph(const vector<T> &v, bool dir = false)
    {
        directed = dir;
        nv = v.size();
        vertices = v;
        for(int i = 0;i < nv; ++i)
            iov[v[i]] = i;      // 记录节点信息与节点序号映射关系
    }

    // 指定节点数量构造 此时节点信息类型必须为 string 
    Graph(unsigned int numOfVertices, bool dir = false)
    {
        directed = dir;
        nv = numOfVertices;
        vertices.resize(nv);
        for(int i = 0;i < nv; ++i)
            vertices[i] = to_string(i);
        for(int i = 0;i < nv; ++i)
            iov[to_string(i)] = i;
    }

    virtual void print() = 0;    // 纯虚函数 Graph不能构造对象

    virtual void insertV()
    {
        insertV(to_string(nv));
    }

    virtual bool insertV(const T nodeInfo)  // 基类插入节点操作
    {
        if(iov.find(nodeInfo) != iov.end() )
            return false;           // 若节点已经存在 插入失败
        vertices.push_back(nodeInfo);
        iov[nodeInfo] = nv;
        ++nv;
        return true;
    }

    virtual bool removeE(const T src, const T dest)
    {
        if(iov.find(src) == iov.end() || iov.find(dest) == iov.end())
            return false;
        return this->removeE(iov[src], iov[dest]);
    }

    virtual bool removeE(const int src, const int dest) = 0;     // 删除边

    virtual int findE(const T nodeInfo)    // 查找边
    {
        auto info = iov.find(nodeInfo);
        if(info == iov.end())
            return -1;
        return info->second;
    }

    virtual void dfs(const T &nodeInfo)
    {
        if(iov.find(nodeInfo) == iov.end())
            return;
        visited.resize(nv);
        for(int i = 0;i < nv; ++i)
            visited[i] = false;      // 设置为未访问过
        dfs(iov[nodeInfo], NULL);
        cout << endl;
    }

    virtual void dfs(const T &nodeInfo, void (*visit) (T &))
    {
        if(iov.find(nodeInfo) == iov.end())
            return;
        visited.resize(nv);
        for(int i = 0;i < nv; ++i)
            visited[i] = false;      // 设置为未访问过
        dfs(iov[nodeInfo], visit);
    }
    
    virtual void bfs(const T &nodeInfo)
    {
        bfs(nodeInfo, NULL);
    }

    virtual void bfs(const T &nodeInfo, void (*visit) (T &)) = 0;

};

#endif