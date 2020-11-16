#ifndef BINARY_TREE_NODE
#define BINARY_TREE_NODE

template<class T>
struct BTNode{
    T data;
    BTNode<T> *lchild;
    BTNode<T> *rchild;

    //构造函数
    BTNode(T value)
    {
        this->data = value;
        lchild = NULL;
        rchild = NULL;
    }
    BTNode()
    {
        lchild = NULL;
        rchild = NULL;
    }
};

#endif