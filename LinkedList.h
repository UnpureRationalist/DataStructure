#include "Vector.h"
template <class T>
struct Node
{
    T data;
    Node<T> *next = NULL;
};

template <class T>
class LinkedList
{
private:
    Node<T> *head;

    void memoryError()
    {
        cerr << "Memory Error!\n";
        exit(-1);
    }

public:
    LinkedList()
    {
        head = new Node<T>();
        if (head == NULL)
            memoryError();
    }

    //用数组顺序构造 尾插法
    LinkedList(T *a, int length)
    {
        head = new Node<T>();
        if (head == NULL)
            memoryError();
        Node<T> *p = head;
        for (int i = 0; i < length; ++i)
        {
            Node<T> *s = new Node<T>();
            if (s == NULL)
                memoryError();
            s->data = a[i];
            p->next = s;
            p = s;
        }
    }

    //用已有链表构造
    LinkedList(LinkedList<T> &exist)
    {
        head = new Node<T>();
        if (head == NULL)
            memoryError();
        Node<T> *p = head;
        Node<T> *pexist = exist.head;
        while (pexist = pexist->next)
        {
            Node<T> *s = new Node<T>();
            if (s == NULL)
                memoryError();
            s->data = pexist->data;
            p->next = s;
            p = s;
        }
    }

    //用向量构造
    LinkedList(ArrayList<T> &v)
    {
        head = new Node<T>();
        if (head == NULL)
            memoryError();
        Node<T> *p = head;
        int length = v.getLength();
        for(int i = 0;i < length; ++i)
        {
            Node<T> *s = new Node<T>();
            if(s == NULL)
                memoryError();
            s->data = v[i];
            p->next = s;
            p = s;
        }
    }
    ~LinkedList()
    {
        Node<T> *p = head;
        while (p != NULL)
        {
            Node<T> *temp = p->next;
            delete p;
            p = temp;
        }
    }

    //计算元素数量
    int size()
    {
        int count = 0;
        Node<T> *p = head;
        while (p = p->next)
            count++;
        return count;
    }

    //遍历输出
    void traverse()
    {
        Node<T> *p = head;
        while (p = p->next)
            cout << p->data << " ";
        cout << endl;
    }

    //在位置k插入一个元素 从1开始计算
    bool insert(int k, T value)
    {
        Node<T> *p = head;
        int count = 0;
        while (p && count < k - 1)
        {
            count++;
            p = p->next;
        }
        if (!p || count > k - 1)
        { //插入位置非法
            return false;
        }
        else
        {
            Node<T> *s = new Node<T>();
            if (s == NULL)
                memoryError();
            s->data = value;
            s->next = p->next;
            p->next = s;
        }
    }

    //删除位置k元素 从1开始计算
    bool erase(int k)
    {
        Node<T> *pre = head;
        Node<T> *p = head->next;
        int count = 1;
        while(p && count < k)
        {
            p = p->next;
            pre = pre->next;
            count++;
        }
        if(count > k || p == NULL)
        {
            return false;
        }
        pre->next = p->next;
        delete p;
        return true;
    }

    //查找等于value的第一个元素 返回地址
    T* find(T value)
    {
        Node<T> *p = head;
        while (p = p->next)
        {
            if(p->data == value)
                return &(p->data);
        }
        return NULL;
    }

    //清空
    void clear()
    {
        Node<T> *p = head->next;
        while (p)
        {
            Node<T> *temp = p;
            p = p->next;
            delete temp;
        }
        head->next = NULL;
    }

    //删除所有等于value 的元素
    void remove(T value)
    {
        Node<T> *pre = head;
        Node<T> *p = head->next;
        while (p)
        {
            if(p->data == value)
            {
                Node<T> *temp = p;
                pre->next = p->next;
                p = p->next;
                delete temp;
            }
            else
            {
                p = p->next;
                pre = pre->next;
            }
            
        }
    }

    //逆序
    void reverse()
    {
        /*
            参考: 单向链表逆序
                https://wenku.baidu.com/view/ee9f791552d380eb62946df9.html
        */
        if(head->next == NULL || head->next->next == NULL)
            return;
        Node<T> *p1 = head->next;
        Node<T> *p2 = p1->next, *p3;
        p1->next = NULL;
        while(p2)
        {
            p3 = p2->next;
            p2->next = p1;
            p1 = p2;
            p2 = p3;
        }
        head->next = p1;
    }

    //升序排序
    void sort()
    {
        if(head->next == NULL || head->next->next == NULL)
            return;
        Node<T> *p = head->next;
        Node<T> *q, *r;
        if(p != NULL)
        {
            r = p->next;
            p->next = NULL;
            p = r;
            while (p != NULL)
            {
                r = p->next;
                q = head;
                while (q->next != NULL && q->next->data < p->data)
                    q = q->next;
                p->next = q->next;
                q->next = p;
                p = r;
            }
        }
    }
};