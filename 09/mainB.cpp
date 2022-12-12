#include <iostream>
#include <string>
#include <set>
#include <tuple>
#include <sstream>
#include <cmath>
#include <vector>

struct Pos
{
    int x = 0;
    int y = 0;
};

int main()
{
    std::set<std::pair<int, int>> visited;
    visited.insert({0, 0});

    std::vector<Pos> knots(10);

    auto move = [&] (int dx, int dy, int count) mutable
    {
        for (int i = 0; i < count; ++i)
        {
            knots[0].x += dx;
            knots[0].y += dy;

            for (int j = 1; j < knots.size(); ++j)
            {
                int delta_x = knots[j-1].x - knots[j].x;
                int delta_y = knots[j-1].y - knots[j].y;

                if (std::abs(delta_x) > 1 || std::abs(delta_y) > 1)
                {
                    if (delta_x != 0)
                        knots[j].x += delta_x/std::abs(delta_x);
                    if (delta_y != 0)
                        knots[j].y += delta_y/std::abs(delta_y);
                }
            }

            visited.insert({knots.back().x, knots.back().y});
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
}