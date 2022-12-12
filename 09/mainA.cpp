#include <iostream>
#include <string>
#include <set>
#include <tuple>
#include <sstream>
#include <cmath>

int main()
{
    std::set<std::pair<int, int>> visited;
    visited.insert({0, 0});

    int head_x = 0, head_y = 0;
    int tail_x = 0, tail_y = 0;

    auto move = [&] (int dx, int dy, int count) mutable
    {
        for (int i = 0; i < count; ++i)
        {
            int new_x = head_x + dx;
            int new_y = head_y + dy;

            if (std::abs(new_x - tail_x) > 1 || std::abs(new_y - tail_y) > 1)
            {
                tail_x = head_x;
                tail_y = head_y;
                visited.insert({tail_x, tail_y});
            }

            head_x = new_x;
            head_y = new_y;
        }
    };

    std::string line;
    while (std::getline(std::cin, line))
    {
        std::stringstream ss(line);

        char dir;
        int count;
        ss >> dir >> count;

        if (dir == 'U')
            move(0, 1, count);
        else if (dir == 'R')
            move(1, 0, count);
        else if (dir == 'D')
            move(0, -1, count);
        else if (dir == 'L')
            move(-1, 0, count);
    }

    std::cout << visited.size() << "\n";

    return 0;
}