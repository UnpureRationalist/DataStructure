#ifndef TEMPLATENODE
#define TEMPLATENODE

template <class T>
struct Node
{
    T data;
    Node<T> *next = NULL;
};

#endif