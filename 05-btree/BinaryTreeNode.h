#ifndef BINARY_TREE_NODE
#define BINARY_TREE_NODE

template <class T>
struct BTNode
{
    T data;
    BTNode<T> *lchild;
    BTNode<T> *rchild;
    int h;  //  用于AVL树节点高度计算

    //构造函数
    BTNode(T value)
    {
        this->data = value;
        lchild = NULL;
        rchild = NULL;
        h = 0;
    }
    BTNode()
    {
        lchild = NULL;
        rchild = NULL;
        h = 0;
    }
};

#endif