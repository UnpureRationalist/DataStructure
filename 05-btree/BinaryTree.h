#ifndef BINARY_TREE
#define BINARY_TREE

#include <iostream>
#include <stdlib.h>
#include "BinaryTreeNode.h"
#include "../03-stack/Stack.h"
#include "../04-queue/Queue.h"
using namespace std;

//输出一个节点的数据
template <class T>
void InnerDefaultPrintOneNodeFunction(T *p)
{
    cout << *p << "  ";
}

template <class T>
class BinaryTree
{
protected:
    BTNode<T> *root = NULL; //根节点指针

    //new失败时调用 结束程序
    void memoryError()
    {
        cerr << "Memory Limit Exceeded!\n";
        exit(-1);
    }

    //析构函数调用 后序遍历释放内存
    void releaseMemory(BTNode<T> *p)
    {
        if (p)
        {
            releaseMemory(p->lchild);
            releaseMemory(p->rchild);
            delete p;
        }
    }

    //递归构造
    void rCreate(T *a, int *index, int length, BTNode<T> *father, bool isLeft, T endFlag)
    {
        if (*index >= length)
            return;
        T value = a[(*index)];
        *index = *index + 1;
        if (value != endFlag)
        {
            BTNode<T> *temp = new BTNode<T>(value);
            if (temp == NULL)
                memoryError();
            if (isLeft)
                father->lchild = temp;
            else
                father->rchild = temp;
            rCreate(a, index, length, temp, true, endFlag);
            rCreate(a, index, length, temp, false, endFlag);
        }
    }

    //先序遍历 递归查找元素 返回   值   的指针(安全角度考虑 不能把节点地址暴露给用户)
    T *rFind(BTNode<T> *p, T value)
    {
        if (p == NULL)
            return NULL;
        if (p->data == value)
            return &(p->data);
        T *found = rFind(p->lchild, value);
        return found ? found : rFind(p->rchild, value);
    }

    //先序遍历 递归查找元素 返回   节点  的指针
    /*
        从内存角度讲,值的指针和节点的指针相同(应该是的?),但为了避免强制类型转换 再写一个inFind函数 返回二叉树节点的地址
    */
    BTNode<T> *inFind(BTNode<T> *p, T value)
    {
        if (p == NULL)
            return NULL;
        if (p->data == value)
            return p;
        BTNode<T> *found = inFind(p->lchild, value);
        return found ? found : inFind(p->rchild, value);
    }

    //递归先序遍历
    void rPreOrder(BTNode<T> *p)
    {
        if (p)
        {
            cout << p->data << "  ";
            rPreOrder(p->lchild);
            rPreOrder(p->rchild);
        }
    }

    //递归中序遍历
    void rInOrder(BTNode<T> *p)
    {
        if (p)
        {
            rInOrder(p->lchild);
            cout << p->data << "  ";
            rInOrder(p->rchild);
        }
    }

    //递归后序遍历
    void rPostOrder(BTNode<T> *p)
    {
        if (p)
        {
            rPostOrder(p->lchild);
            rPostOrder(p->rchild);
            cout << p->data << "  ";
        }
    }

    //打印树 利用中序遍历
    void display(BTNode<T> *p, int level)
    {
        if (p)
        {
            display(p->rchild, level + 1);
            cout << endl;
            for (int i = 0; i < level - 1; i++)
                cout << "   ";
            cout << p->data;
            display(p->lchild, level + 1);
        }
    }

    //统计叶子节点数目
    int rCountLeaves(BTNode<T> *p)
    {
        if (p == NULL)
            return 0;
        if (p->lchild == NULL && p->rchild == NULL)
            return 1;
        return rCountLeaves(p->lchild) + rCountLeaves(p->rchild);
    }

    //计算二叉树高度
    int rDepth(BTNode<T> *p)
    {
        if (p == NULL)
            return 0;
        if (p->lchild == NULL && p->rchild == NULL)
            return 1;
        return 1 + max(rDepth(p->lchild), rDepth(p->rchild));
    }

public:
    BinaryTree()
    {
        root = NULL;
    }

    //给根节点赋值构造二叉树
    BinaryTree(T rootValue)
    {
        root = new BTNode<T>(rootValue);
        if (root == NULL)
            memoryError();
    }

    //根据前序遍历数组构造 3个参数分别为: 数组首地址  数组长度  空节点标志值
    BinaryTree(T *a, int length, T endFlag)
    {
        if (length >= 1)
        {
            root = new BTNode<T>(a[0]);
            if (root == NULL)
                memoryError();
            int i = 1;
            rCreate(a, &i, length, root, true, endFlag);
            rCreate(a, &i, length, root, false, endFlag);
        }
    }

    //析构函数
    ~BinaryTree()
    {
        releaseMemory(root);
    }

    //查找 返回指针 失败返回NULL
    T *find(T value)
    {
        return rFind(root, value);
    }

    //插入
    bool insert(T value, bool isLeft, T fatherValue)
    {
        BTNode<T> *found = inFind(root, fatherValue);
        if (found == NULL)
            return false;
        BTNode<T> *s = new BTNode<T>(value);
        if (s == NULL)
            return false; //此处没有调用 memoryError(); 考虑到插入失败是可以接受的 没必要退出程序
        if (isLeft)       //插在左孩子指针位置
        {
            if (found->lchild != NULL) //左子树非空 插入失败
                return false;
            else
                found->lchild = s;
        }
        else //插在右孩子指针位置
        {
            if (found->rchild != NULL)
                return false;
            else
                found->rchild = s;
        }
        return true;
    }

    //递归先序遍历
    void preOrderTraverse()
    {
        rPreOrder(root);
        cout << endl;
    }

    //递归中序遍历
    void inOrderTraverse()
    {
        rInOrder(root);
        cout << endl;
    }

    //递归后序遍历
    void postOrderTraverse()
    {
        rPostOrder(root);
        cout << endl;
    }

    //迭代先序遍历 自定义函数指针传入 默认为打印
    void iPreOrderTraverse(void(traverse)(T *))
    {
        BTNode<T> *p = root;
        Stack<BTNode<T> *> s;
        while (p || !s.isEmpty())
        {
            if (p) //遍历左子树并进栈
            {
                traverse(&(p->data));
                s.push(p);
                p = p->lchild;
            }
            else
            {
                p = s.pop();
                p = p->rchild;
            }
        }
    }

    //函数重载 非递归先序遍历 默认为打印
    void iPreOrderTraverse()
    {
        iPreOrderTraverse(InnerDefaultPrintOneNodeFunction);
        cout << endl;
    }

    //迭代中序遍历
    void iInOrderTraverse(void(traverse)(T *))
    {
        BTNode<T> *p = root;
        Stack<BTNode<T> *> s;
        while (p || !s.isEmpty())
        {
            if (p)
            {
                s.push(p);
                p = p->lchild;
            }
            else
            {
                p = s.pop();
                traverse(&(p->data)); //遍历
                p = p->rchild;
            }
        }
    }

    //函数重载 非递归中序遍历 默认为打印
    void iInOrderTraverse()
    {
        iInOrderTraverse(InnerDefaultPrintOneNodeFunction);
        cout << endl;
    }

    //迭代后序遍历
    void iPostOrderTraverse(void(traverse)(T *))
    {
        BTNode<T> *p = root;
        Stack<BTNode<T> *> s;
        Stack<bool> flagStack;
        while (p || !s.isEmpty())
        {
            if (p)
            {
                s.push(p);
                flagStack.push(1);
                p = p->lchild;
            }
            else
            {
                p = s.pop();
                bool flag = flagStack.pop();
                if (flag) //第 1 次出现在栈顶
                {
                    s.push(p);
                    flagStack.push(0);
                    p = p->rchild;
                }
                else
                {
                    traverse(&(p->data));
                    p = NULL;
                }
            }
        }
    }

    //函数重载 非递归后序遍历 默认为打印
    void iPostOrderTraverse()
    {
        iPostOrderTraverse(InnerDefaultPrintOneNodeFunction);
        cout << endl;
    }

    //层次遍历
    void levelTraverse(void(traverse)(T *))
    {
        BTNode<T> *p;
        Queue<BTNode<T> *> q;
        if (root)
        {
            q.push(root);
            while (!q.isEmpty())
            {
                p = q.pop();
                traverse(&(p->data));
                if (p->lchild)
                    q.push(p->lchild);
                if (p->rchild)
                    q.push(p->rchild);
            }
        }
    }

    //缺省层次遍历 打印
    void levelTraverse()
    {
        levelTraverse(InnerDefaultPrintOneNodeFunction);
        cout << endl;
    }

    //打印树结构
    void print()
    {
        display(root, 1);
        cout << endl;
    }

    //计算叶子数目
    int countLeaves()
    {
        return rCountLeaves(root);
    }

    //计算二叉树深度
    int depth()
    {
        return rDepth(root);
    }

    //统计节点数目 利用先序遍历
    int countNodes()
    {
        int count = 0;
        BTNode<T> *p = root;
        Stack<BTNode<T> *> s;
        while (p || !s.isEmpty())
        {
            if (p) //遍历左子树并进栈
            {
                count++; //统计节点数目
                s.push(p);
                p = p->lchild;
            }
            else
            {
                p = s.pop();
                p = p->rchild;
            }
        }
        return count;
    }
};

#endif