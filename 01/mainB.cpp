#include <iostream>
#include <string>
#include <sstream>
#include <array>

void insert(std::array<int, 3>& maxes, int sum)
{
    if (sum > maxes[0])
    {
        maxes[0] = sum;
        if (maxes[0] > maxes[1]) std::swap(maxes[0], maxes[1]);
        if (maxes[1] > maxes[2]) std::swap(maxes[1], maxes[2]);
    }
}

int main()
{
    std::array<int, 3> maxes = { 0, 0, 0 };
    int sum = 0;

    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line.empty())
        {
            insert(maxes, sum);
            sum = 0;
        } else {
            std::stringstream ss(line);

            int calories;
            ss >> calories;

            sum += calories;
        }
    }

    insert(maxes, sum);

    std::cout << maxes[0] + maxes[1] + maxes[2] << "\n";
}