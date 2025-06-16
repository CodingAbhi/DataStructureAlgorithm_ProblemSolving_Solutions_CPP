#include <bits/stdc++.h>
using namespace std;
#define n 100
class sstack
{
    int *arr;
    int top;

public:
    sstack()
    {
        arr = new int[n];
        top = -1;
    }

    void push(int x)
    {
        if (top == (n - 1))
        {
            cout << "overflow" << endl;
            return;
        }
        top++;
        arr[top] = x;
    }

    void pop()
    {
        if (top == -1)
        {
            cout << "No element to pop" << endl;
            return;
        }
        top--;
    }
    int Top()
    {
        if (top == -1)
        {
            cout << "No element in stack" << endl;
            return -1;
        }
        else
        {
            return arr[top];
        }
    }
    bool isempty()
    {
        return top == -1;
    }
};

int main()
{
    sstack st;
    st.push(3);
    st.push(5);
    st.push(8);
    cout << st.Top() << endl;
    st.pop();
    cout << st.Top() << endl;
    st.pop();
    cout << st.Top() << endl;
    st.pop();
    cout << st.Top() << endl;
    st.push(9);
    cout << st.Top() << endl;
    cout << st.isempty() << endl;
}