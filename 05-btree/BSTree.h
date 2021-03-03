#ifndef BINARARY_SEARCH_TREE
#define BINARARY_SEARCH_TREE
#include <iostream>
#include "BinaryTree.h"

template <class T>
class BSTree : public BinaryTree<T>
{ // 继承自二叉树
public:
    BSTree()
    {
        this->root = NULL;
    }

    T *findMax()
    {
        if (this->root == NULL)
            return NULL;
        BTNode<T> *temp = this->root;
        while (temp->rchild)
        {
            temp = temp->rchild;
        }
        return temp;
    }

    T *findMin()
    {
        if (this->root == NULL)
            return NULL;
        BTNode<T> *temp = this->root;
        while (temp->Lchild)
        {
            temp = temp->Lchild;
        }
        return temp;
    }

    T *findX(T x)
    {
        if (this->root == NULL)
            return NULL;
        BTNode<T> *temp = this->root;
        while (temp && temp->data != x)
        {
            if (temp->data > x)
                temp = temp->lchild;
            else
                temp = temp->rchild;
        }
        return temp;
    }

    bool insert(T value)
    {
        try
        {
            this->root = rinsert(value, this->root);
        }
        catch (int e)
        {
            if (e == -1)
                cerr << "ERROR: Mermory Limit Exceeded!" << endl;
            else if (e == -2)
                cerr << "ERROR: Same Element Existing!" << endl;
            return false; // 插入失败
        }
        return true;
    }

    bool remove(T value)
    {
        try
        {
            this->root = rremove(value, this->root);
        }
        catch (int e)
        {
            return false; // 删除失败
        }
        return true;
    }

    // 无需定义析构函数 会调用父类析构函数释放内存

protected:
    BTNode<T> *rfindMax(BTNode<T> *r)
    { // 递归实现 效率低
        if (r == NULL)
            return NULL;
        if (r->rchild == NULL)
            return r;
        return rfindMax(r->rchild);
    }

    virtual BTNode<T> *rinsert(T x, BTNode<T> *p) // 加virtual动态联编
    {
        if (p == NULL)
        { // 找到插入位置 递归结束
            p = new BTNode<T>(x);
            if (p == NULL)
            {
                throw -1; // 内存不够
            }
        }
        else if (p->data > x)
            p->lchild = rinsert(x, p->lchild);
        else if (p->data < x)
            p->rchild = rinsert(x, p->rchild);
        else
        {
            throw -2; // 元素重复
        }
        return p;
    }

    BTNode<T> *rremove(T x, BTNode<T> *p)
    {
        if (p == NULL)
        {
            throw -1; // 删除失败
        }
        else if (p->data == x)
        {
            if (p->lchild && p->rchild)
            { // 左右子树都非空
                BTNode<T> *temp = rfindMax(p->lchild);
                p->data = temp->data;
                p->lchild = rremove(temp->data, p->lchild);
            }
            else
            {
                BTNode<T> *temp = p;
                p = p->lchild ? p->lchild : p->rchild;
                delete temp;
            }
        }
        else if (p->data > x)
        {
            p->lchild = rremove(x, p->lchild);
        }
        else
        {
            p->rchild = rremove(x, p->rchild);
        }
        return p;
    }
};

#endif