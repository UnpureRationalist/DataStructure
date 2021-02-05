#ifndef AVL_TREE
#define AVL_TREE

#include <iostream>
#include "BSTree.h"

template<class T>
class AVLTree : public BSTree<T>
{
    protected:
        int height(BTNode<T> *p)
        {
            if(p == NULL)
                return -1;
            else
                return p->h;
        }

        // 把p作为树根的树进行LL旋转 完成后把最新的树根返回
        BTNode<T>* LLrotate(BTNode<T> *p)
        {
            BTNode<T> *child = p->lchild;
            p->lchild = child->rchild;
            child->rchild = p;
            p->h = max(height(p->lchild), height(p->rchild)) + 1;
            child->h = max(height(child->lchild), height(child->rchild)) + 1;   // 更新高度
            return child;
        }

        BTNode<T>* RRrotate(BTNode<T> *p)
        {
            BTNode<T> *child = p->rchild;
            p->rchild = child->lchild;
            child->lchild = p;
            p->h = max(height(p->lchild), height(p->rchild)) + 1;
            child->h = max(height(child->lchild), height(child->rchild)) + 1;   // 更新高度
            return child;
        }

        BTNode<T>* LRrotate(BTNode<T> *p)
        {
            p->lchild = RRrotate(p->lchild);
            return LLrotate(p);
        }

        BTNode<T>* RLrotate(BTNode<T> *p)
        {
            p->rchild = LLrotate(p->rchild);
            return RRrotate(p);
        }

        BTNode<T>* rinsert(T x, BTNode<T> *p)
        {
            if(p == NULL)
            {   // 找到插入位置 递归结束
                p = new BTNode<T>(x);
                if(p == NULL)
                {
                    throw -1;   // 内存不够
                }
            }
            else if(p->data > x)
            {
                p->lchild = rinsert(x, p->lchild);
                if(height(p->lchild) - height(p->rchild) == 2)
                {
                    if(x < p->lchild->data) // LL
                    {
                        p = LLrotate(p);
                    }
                    else
                    {
                        p = LRrotate(p);
                    }
                }
            }
            else if(p->data < x)
            {
                p->rchild = rinsert(x, p->rchild);
                if(height(p->rchild) - height(p->lchild) == 2)
                {
                    if(x > p->rchild->data) // RR
                    {
                        p = RRrotate(p);
                    }
                    else
                    {
                        p = RLrotate(p);
                    }
                }
            }
            else
            {
                throw -2;   // 元素重复
            }
            p->h = max(height(p->lchild), height(p->rchild)) + 1;   // 更新高度
            return p;
        }

    public:
        AVLTree()
        {
            this->root = NULL;
        }

        /*
        * 此处 AVL 树从二叉树 二叉搜索树中继承了许多成员函数 一些操作是 AVL 树不允许的 实际使用应该加以限制
        * 另外,此处未实现 AVL 树的删除操作
        */
};

#endif