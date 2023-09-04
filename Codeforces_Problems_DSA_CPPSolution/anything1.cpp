#include <iostream>
#include <vector>

using namespace std;

vector<int> combine_vectors(vector<int> vector1, vector<int> vector2)
{
    vector<int> combined;
    for (int i = 0; i < min(vector1.size(), vector2.size()); i++)
    {
        combined.push_back(vector1[i]);
        combined.push_back(vector2[i]);
    }
    if (vector1.size() > vector2.size())
    {
        for (int i = vector2.size(); i < vector1.size(); i++)
        {
            combined.push_back(vector1[i]);
        }
    }
    else if (vector2.size() > vector1.size())
    {
        for (int i = vector1.size(); i < vector2.size(); i++)
        {
            combined.push_back(vector2[i]);
        }
    }
    return combined;
}

int main()
{
    vector<int> v1 = {1, 3, 5, 7};
    vector<int> v2 = {2, 4, 6};
    vector<int> combined = combine_vectors(v1, v2);
    for (int i = 0; i < combined.size(); i++)
    {
        cout << combined[i] << " ";
    }
    cout << endl;
    return 0;
}
