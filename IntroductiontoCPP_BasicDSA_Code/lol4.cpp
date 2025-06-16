#include <iostream>
#include <cstring>

int solve(char *S)
{
    int map[26] = {0};
    int len = strlen(S);

    for (int i = 0; i < len; i++)
    {
        map[S[i] - 'a']++;
    }

    int sublen = 0;
    int count = 0;

    for (int i = 0; i < 26; i++)
    {
        if (map[i] > 0)
        {
            sublen += map[i] - (map[i] % 2);
            count += (map[i] % 2);
        }
    }

    if (count > 0)
    {
        sublen++;
    }

    return sublen;
}

int main()
{
    // Example usage:
    char input[] = "abacabad";
    int result = solve(input);

    // Display the result
    std::cout << "Result: " << result << std::endl;

    return 0;
}
