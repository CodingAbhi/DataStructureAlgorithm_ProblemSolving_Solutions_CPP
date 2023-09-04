#include <bits/stdc++.h>
using namespace std;
class stackusingarray
{
    int *data;
    int nextidx;
    int capacity;

public:
    stackusingarray(int totalsize)
    {
        data = new int[totalsize];
        nextidx = 0;
        capacity = totalsize;
    }

    int size()
    {
        return nextidx;
    }
    bool isEmpty()
    {
        return nextidx == 0;
    }
    void push(int element)
    {
        if (nextidx == capacity)
        {
            cout << "Stack Overflowed" << endl;
            return;
        }
        data[nextidx] = element;
        nextidx++;
    }
    int pop()
    {
        if (isEmpty())
        {
            cout << "Stack is Empty" << endl;
            return INT_MIN;
        }
        nextidx--;
        return data[nextidx];
    }

    int top()
    {
        if (isEmpty())
        {
            cout << "Stack is Empty" << endl;
            return INT_MIN;
        }
        return data[nextidx - 1];
    }
};
