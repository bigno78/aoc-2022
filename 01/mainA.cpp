#include <iostream>
#include <string>
#include <sstream>

int main()
{
    int max = 0;
    int sum = 0;

    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line.empty())
        {
            max = sum > max ? sum : max;
            sum = 0;
        }

        std::stringstream ss(line);

        int calories;
        ss >> calories;

        sum += calories;
    }

    max = sum > max ? sum : max;

    std::cout << max << "\n";
}
