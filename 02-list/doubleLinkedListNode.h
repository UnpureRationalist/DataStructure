#ifndef DOUBLE_LINKED_LIST_NODE
#define DOUBLE_LINKED_LIST_NODE

template <typename ElemType>
struct doubleLinkedListNode
{
    ElemType data;                        // 数据
    doubleLinkedListNode<ElemType> *next; // 指向后面节点指针
    doubleLinkedListNode<ElemType> *pre;  // 指向前面节点指针

    doubleLinkedListNode() : next(nullptr), pre(nullptr) {}
    doubleLinkedListNode(const ElemType &ref) : data(ref), next(nullptr), pre(nullptr) {}
};

#endif