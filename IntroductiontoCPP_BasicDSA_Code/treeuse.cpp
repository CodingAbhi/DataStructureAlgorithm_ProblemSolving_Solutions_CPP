#include <bits/stdc++.h>
using namespace std;
#include "treenode.cpp"
void printree(Treenode<int> *root)
{
    if(root==NULL){
        return;
    }
    cout << root->data << ":";
    for (int i = 0; i < root->children.size(); i++)
    {
        cout << root->children[i]->data << ",";
    }
    cout << endl;
    for (int i = 0; i < root->children.size(); i++)
    {
        printree(root->children[i]);
    }
}
int main()
{
    Treenode<int> *root = new Treenode<int>(1);
    Treenode<int> *node1 = new Treenode<int>(2);
    Treenode<int> *node2 = new Treenode<int>(3);

    root->children.push_back(node1);
    root->children.push_back(node2);

    printree(root);
}