#include <iostream>
#include "BinaryTree.h"
using namespace std;

//将二叉树所有节点增加1
void increaseOne(int *p)
{
    *p = *p + 1;
}

int main()
{
    BinaryTree<int> intTree(1);
    //插入
    intTree.insert(2, 1, 1);
    intTree.insert(3, 0, 1);
    intTree.insert(4, 1, 2);
    intTree.insert(8, 0, 2);
    intTree.insert(5, 0, 3);
    intTree.insert(6, 1, 3);
    intTree.insert(10, 0, 8);
    cout << "二叉树结构:\n";
    intTree.print();
    cout << "递归遍历:\n";
    intTree.preOrderTraverse();
    intTree.inOrderTraverse();
    intTree.postOrderTraverse();
    //非递归遍历
    cout << "非递归遍历:\n";
    intTree.iPreOrderTraverse();
    intTree.iInOrderTraverse();
    //后序遍历 将二叉树所有元素增加1
    intTree.iPostOrderTraverse(increaseOne);
    cout << "二叉树结构:\n";
    intTree.print();
    intTree.iPostOrderTraverse();
    cout << "层次遍历:\n";
    intTree.levelTraverse();
    intTree.insert(100, 0, 11);
    cout << "二叉树结构:\n";
    intTree.print();
    cout << "节点数 = " << intTree.countNodes() << endl;
    cout << "叶子节点数 = " << intTree.countLeaves() << endl;
    cout << "二叉树高度 = " << intTree.depth() << endl;
    //由先序遍历数组构造二叉树  0 标志空节点
    /*
                                10
                               /   \
                            20      30
                           /   \
                         40     50
                              /   \
                            60     70
                                  /
                                80
                                   \
                                    90
    */
    double array[] = {10, 20, 40, 0, 0, 50, 60, 0, 0, 70, 80, 0, 90, 0, 0, 0, 30, 0, 0};
    int length = sizeof(array)/sizeof(double);
    BinaryTree<double> doubleTree(array, length, 0);
    doubleTree.print();
    cout << "层次遍历:\n";
    doubleTree.levelTraverse();
    cout << "递归先序遍历:\n";
    doubleTree.preOrderTraverse();
    return 0;
}