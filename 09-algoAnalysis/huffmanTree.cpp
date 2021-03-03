#include <iostream>
#include <vector>
#include "HuffmanTree.h"
using namespace std;
/*
7
10 15 12 3 4 13 1
*/
int main()
{
    vector<HuffmanTree<int>> nodes;
    int n, weight;
    cin >> n;
    for(int i = 0;i < n; ++i)
    {
        cin >> weight;
        nodes.emplace_back(weight);
    }
    HuffmanTree<int> ht(nodes);
    ht.print();
    return 0;
}