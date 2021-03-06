#include <iostream>
#include <vector>
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
  cout << "binary tree construct:\n";
  intTree.print();
  cout << "recursion traverse:\n";
  intTree.preOrderTraverse();
  intTree.inOrderTraverse();
  intTree.postOrderTraverse();
  //非递归遍历
  cout << "no recursion traverse:\n";
  intTree.iPreOrderTraverse();
  intTree.iInOrderTraverse();
  //后序遍历 将二叉树所有元素增加1
  intTree.iPostOrderTraverse(increaseOne);
  cout << "binary tree construct:\n";
  intTree.print();
  intTree.iPostOrderTraverse();
  cout << "level traverse:\n";
  intTree.levelTraverse();
  intTree.insert(100, 0, 11);
  cout << "binary tree construct:\n";
  intTree.print();
  cout << "num of nodes = " << intTree.countNodes() << endl;
  cout << "num of leaves = " << intTree.countLeaves() << endl;
  cout << "height of binary tree = " << intTree.depth() << endl;
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
  int length = sizeof(array) / sizeof(double);
  BinaryTree<double> doubleTree(array, length, 0);
  doubleTree.print();
  cout << "level traverse:\n";
  doubleTree.levelTraverse();
  cout << "recursion preOrder traverse:\n";
  doubleTree.preOrderTraverse();
  cout << "____________________________________________________________" << endl;
  cout << "____________________________________________________________" << endl;
  /* 先序、中序、后序
    1  2  4  8  10  3  6  5
    4  2  8  10  1  6  3  5
    4  10  8  2  6  5  3  1
  */
  vector<int> preorder{1, 2, 4, 8, 10, 3, 6, 5}, inorder{4, 2, 8, 10, 1, 6, 3, 5}, postorder{4, 10, 8, 2, 6, 5, 3, 1};
  BinaryTree<int> test1(preorder, inorder);
  cout << "test1 postOrder traverse:" << endl;
  test1.postOrderTraverse();
  BinaryTree<int> test2(inorder, postorder, true);
  cout << "\ntest2 preOrder traverse:" << endl;
  test2.preOrderTraverse();
  return 0;
}