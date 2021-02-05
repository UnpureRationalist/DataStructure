#include <iostream>
#include "BSTree.h"
using namespace std;
int main()
{
    BSTree<int> intBSTree;
    intBSTree.insert(10);
    intBSTree.insert(15);
    intBSTree.insert(20);
    intBSTree.insert(18);
    intBSTree.insert(30);
    intBSTree.insert(0);
    intBSTree.insert(-20);
    intBSTree.insert(8);
    intBSTree.insert(7);
    intBSTree.insert(6);
    intBSTree.insert(40);
    intBSTree.insert(50);
    intBSTree.insert(-15);
    intBSTree.insert(-25);
    intBSTree.insert(-35);
    intBSTree.print();
    intBSTree.iInOrderTraverse();
    intBSTree.remove(10);
    intBSTree.print();
    intBSTree.remove(-35);
    intBSTree.print();
    intBSTree.remove(15);
    intBSTree.print();
    intBSTree.remove(30);
    intBSTree.print();
    return 0;
}