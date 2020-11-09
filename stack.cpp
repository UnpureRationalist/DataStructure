#include <iostream>
#include "Stack.h"
using namespace std;

int main()
{
    Stack<int> s;
    int array[] = {-23, -45, 345, 0, 1, 2, 3, 4, 5};
    int length = sizeof(array) / sizeof(int);
    for (int i = 0; i < length; ++i)
        s.push(array[i]);
    for(int i = 0;i < 1024; ++i)
        s.push(i);
    while (!s.isEmpty())
    {
        s.pop();
        if(s.length() <= 10 && s.length() > 0)
            cout << "s.top() = " << s.top() << endl;
    }
    
    return 0;
}