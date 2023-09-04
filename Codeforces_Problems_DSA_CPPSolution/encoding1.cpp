#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

string check_collision(unordered_map<char, int> &mapping, int n)
{
    string result = "NO";
    unordered_map<string, int> encoded_words;
    for (int i = 0; i < n; i++)
    {
        string word;
        cin >> word;
        string encoded_word = "";
        for (char c : word)
        {
            encoded_word += to_string(mapping[c]);
        }
        if (encoded_words.count(encoded_word) > 0)
        {
            result = "YES";
        }
        else
        {
            encoded_words[encoded_word] = 1;
        }
    }
    return result;
}

int main()
{
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        unordered_map<char, int> mapping;
        for (int j = 0; j < 26; j++)
        {
            int digit;
            cin >> digit;
            mapping[char(j + 'A')] = digit;
        }
        int n;
        cin >> n;
        string result = check_collision(mapping, n);
        cout << "Case #" << i << ": " << result << endl;
    }
    return 0;
}
