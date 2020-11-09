template <class T>
struct Node
{
    T data;
    Node<T> *next = NULL;
};