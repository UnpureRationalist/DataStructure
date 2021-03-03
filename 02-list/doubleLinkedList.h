#ifndef DOUBLE_LINKED_LIST
#define DOUBLE_LINKED_LIST

#include <iostream>
#include "doubleLinkedListNode.h"
using namespace std;

template<class T>
class DoubleLinkedList
{
private:
    doubleLinkedListNode<T> *head;

public:
    DoubleLinkedList()
    {
        head = new doubleLinkedListNode<T>();
    }
};

#endif