#ifndef LINKED_LIST_QUEUE
#define LINKED_LIST_QUEUE

#include <iostream>
#include <cstdlib>
#include "Queue.h"
#include "../02-list/templateNode.h"
using namespace std;

template<class T>
class LinkedlistQueue : public Queue<T>
{
private:
    Node<T> *head;
    Node<T> *tail;

public:
    LinkedlistQueue()
    {
        head = new Node<T>();
        if(head == NULL)
            this->memoryError();
        tail = head;
    }
    LinkedlistQueue(T *a,int length)
    {
        head = new Node<T>();
        if(head == NULL)
            this->memoryError();
        tail = head;
        Node<T> *s;
        for(int i = 0;i < length; ++i)
        {
            s = new Node<T>();
            if(s == NULL)
                this->memoryError();
            s->data = a[i];
            tail->next = s;
            tail = s;
        }
    }
    ~LinkedlistQueue()
    {
        Node<T> *s = NULL;
        while (head)
        {
            s = head;
            head = head->next;
            delete s;
        }
    }
    
    bool isEmpty()
    {
        return head == tail;
    }

    //大小
    int size()
    {
        int count = 0;
        Node<T> *s = head;
        while (s = s->next)
        {
            ++count;
        }
        return count;
    }

    //插入
    void push(T value)
    {
        Node<T> *s = new Node<T>();
        if(s == NULL)
            this->memoryError();
        s->data = value;
        tail->next = s;
        tail = s;
    }

    //弹出首个元素 (先进先出)
    T pop()
    {
        if(isEmpty())
            this->emptyError();
        Node<T> *s = head->next;
        T value = s->data;
        head->next = s->next;
        if(head->next == NULL)  //若只剩一个元素 更改尾指针
            tail = head;
        delete s;
        return value;
    }
};

#endif