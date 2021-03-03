/**
  例：推断学生所属学校-C++语言参考代码

  说明：例题中要求输出学校的数量和人数最多的学校学生名单，
  但是在后续的视频讲解中，题目写成了输出人数最多的学校的人数
  以及学生名单。
  特此修正，改为输出学校的数量。修改部分在最后，附有注释。
**/
#include <iostream>
#include <set>
#include <map>
using namespace std;
template<class T>
struct DisjointSet{
    int *parent;
    T *data;
    set<T> *mates;
    map<T, int> m;
    int capacity;
    int size;
    DisjointSet(int max=10){
        capacity = max;
        size = 0;
        parent = new int[max+1];
        data = new T[max+1];
        mates = new set<T>[max+1];
    }
    ~DisjointSet(){
        delete [] parent;
        delete [] data;
    }
    bool insert(T x){
        if(size == capacity) return false;
        size++;
        data[size] = x;
        parent[size] = -1;
        mates[size].insert(x);
        m[x] = size;
        return true;
    }
    int find(T x){
        typename map<T, int>::iterator it;
        it = m.find(x);
        if(it == m.end()) return -1;
        int rt, i;
        i = rt = it->second;
        while(parent[rt]>0)
            rt = parent[rt];
        int tmp;
        for( ; i!=rt; i=tmp){
            tmp = parent[i];
            parent[i] = rt;
        }
        return rt;
    }
    void unionSet(T x, T y){
        int rx, ry;
        rx = find(x);
        ry = find(y);
        if(rx==-1 || ry==-1) return;
        if(rx == ry) return;
        if(parent[rx] < parent[ry]){
            parent[rx] += parent[ry];
            parent[ry] = rx;
            mates[rx].insert(mates[ry].begin(), mates[ry].end());
            mates[ry].clear();
        }
        else{
            parent[ry] += parent[rx];
            parent[rx] = ry;
            mates[ry].insert(mates[rx].begin(), mates[rx].end());
            mates[rx].clear();
        }
    }
    
    void print(){
        for(int i=1; i<=size; i++)
            cout << i << "\t";
        cout << endl;
        for(int i=1; i<=size; i++)
            cout << parent[i] << "\t";
        cout << endl;
        for(int i=1; i<=size; i++)
            cout << data[i] << "\t";
        cout << endl;
    }
};
int main(){
    int M, N;
    cin >> N;
    DisjointSet<string> s(N);
    string name;
    for(int i=0; i<N; i++){
        cin >> name;
        s.insert(name);
    }
    cin >> M;
    string name2;
    for(int i=0; i<M; i++){
        cin >> name >> name2;
        s.unionSet(name, name2);
    }
    
    /* 以下代码有修改 */
    int maxid=0, maxsize=0, numOfSchools=0;  //增加变量numOfSchools:学校数量
    for(int i=1; i<=N; i++){
        if(s.mates[i].size()>0) numOfSchools++; //发现一所学校，则数量+1
        if(s.parent[i] < maxsize) {
            maxsize = s.parent[i];
            maxid = i;
        }
    }
    cout << numOfSchools << endl;  //打印学校的数量
    for(auto x : s.mates[maxid])  //打印人数最多的学校的学生名单
        cout << x << ' ';
    cout << endl;
    return 0;
}
/** 测试数据：
 8
 Bill Ellen Ann Chris Daisy Flin Henry Grace
 5
 Ann Chris
 Ellen Chris
 Daisy Flin
 Henry Ellen
 Grace Flin
*/