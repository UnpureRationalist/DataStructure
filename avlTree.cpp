#include <iostream>
#include "AVLTree.h"
using namespace std;
int main()
{
    AVLTree<int> intAVLTree;
    for(int i = 0;i < 30; ++i)
        intAVLTree.insert(i);
    intAVLTree.print();
    for(int i = -1;i >= -30; --i)
        intAVLTree.insert(i);
    intAVLTree.print();
    intAVLTree.inOrderTraverse();
    return 0;
}