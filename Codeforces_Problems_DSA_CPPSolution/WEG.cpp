#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> printNTimes(int n)
{
    // Create a vector with 'n' copies of the string "Coding Ninjas"
    return std::vector<std::string>(n, "Coding Ninjas");
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<std::string> result = printNTimes(n);

    for (const std::string &str : result)
    {
        std::cout << str << " ";
    }
    std::cout << std::endl;

    return 0;
}
