#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int main()
{
    std::vector<std::vector<char>> stack_table;
    std::string line;

    std::getline(std::cin, line);
    while (line[1] != '1')
    {
        stack_table.emplace_back();
        stack_table.back().reserve(9);

        int i = 1;
        while (i < line.size())
        {
            stack_table.back().push_back(line[i]);
            i += 4;
        }

        std::getline(std::cin, line);
    }

    std::vector<std::vector<char>> stacks(9);

    for (int i = stack_table.size() - 1; i >= 0; --i)
    {
        for (int j = 0; j < 9; ++j)
        {
            if (j < stack_table[i].size() && stack_table[i][j] != ' ')
            {
                stacks[j].push_back(stack_table[i][j]);
            }
        }
    }

    std::string trash;
    int count, from, to;

    std::getline(std::cin, line);
    while(std::getline(std::cin, line))
    {
        std::stringstream ss(line);
        ss >> trash >> count >> trash >> from >> trash >> to;

        if (!ss) break;

        for (int i = 0; i < count; ++i) {
            auto x = stacks[from - 1].back();
            stacks[from - 1].pop_back();
            stacks[to - 1].push_back(x);
        }
    }

    for (int j = 0; j < 9; ++j)
    {
        std::cout << stacks[j].back();
    }
    std::cout << "\n";
}
