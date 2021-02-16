#ifndef HUFFMAN_TREE
#define HUFFMAN_TREE

#include <iostream>
#include <vector>
#include <queue>
#include "BinaryTreeNode.h"
using namespace std;
// 贪心
template<class T>
class HuffmanTree
{
private:
    BTNode<T> *root;

    void MemoryError()
    {
        cerr << "Memory Limit Exceeded!" << endl;
        exit(-1);
    }

    void rprint(BTNode<T> *p, int level)
    {
        if (p)
        {
            rprint(p->rchild, level + 1);
            cout << endl;
            for (int i = 0; i < level - 1; i++)
                cout << "   ";
            cout << p->data;
            rprint(p->lchild, level + 1);
        }
    }

public:
    HuffmanTree()
    {
        root = NULL;
    }

    HuffmanTree(T weight)
    {
        root = new (nothrow) BTNode<T>(weight);
        if(root == NULL)
            MemoryError();
    }

    HuffmanTree(vector<HuffmanTree<T>> &nodes)
    {
        priority_queue<HuffmanTree<T>, vector<HuffmanTree<T>>, greater<HuffmanTree<T>>> q(nodes.begin(), nodes.end());
        HuffmanTree<T> temp;
        for(int i = 1;i < nodes.size(); ++i)
        {
            temp.root = new BTNode<T>();
            temp.root->lchild = q.top().root;
            q.pop();
            temp.root->rchild = q.top().root;
            q.pop();
            temp.root->data = temp.root->lchild->data + temp.root->rchild->data;
            q.push(temp);
        }
        root = q.top().root;
    }

    void print()
    {
        rprint(root , 1);
        cout << endl;
    }

    bool operator > (const HuffmanTree<T> &t) const
    {
        return this->root->data > (t.root)->data; // 运算符重载 比较哈夫曼树根节点数值
    }

    ~HuffmanTree()
    {
        delete root;
    }
};


#endif