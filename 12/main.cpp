#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <queue>
#include <array>

struct Pos
{
    int x, y;
};

int main()
{
    std::vector<std::string> grid;

    Pos start, goal;

    std::string line;
    while (std::getline(std::cin, line))
    {
        for (int i = 0; i < line.size(); ++i)
        {
            if (line[i] == 'S')
                start = { i, (int)grid.size() };
            if (line[i] == 'E')
                goal = { i, (int)grid.size() };
        }
        grid.emplace_back(std::move(line));
    }

    int x_dim = grid.front().size();
    int y_dim = grid.size();

    grid[start.y][start.x] = 'a';
    grid[goal.y][goal.x] = 'z';

    std::vector<std::vector<int>> d(y_dim, std::vector<int>(x_dim, -1));
    std::queue<Pos> q;

    d[goal.y][goal.x] = 0;
    q.push(goal);

    while (!q.empty())
    {
        auto [ x, y ] = q.front();
        q.pop();

        std::array<Pos, 4> neighbors = {
            Pos{ x + 1, y }, Pos{ x - 1, y }, Pos{ x, y + 1}, Pos{ x, y - 1 }
        };

        for (auto [ nx, ny ] : neighbors)
        {
            if (0 <= nx && nx < x_dim && 0 <= ny && ny < y_dim
                && grid[ny][nx] >= grid[y][x] - 1 && d[ny][nx] == -1)
            {
                d[ny][nx] = d[y][x] + 1;
                q.push({ nx, ny });
            }
        }
    }

    std::cout << d[start.y][start.x] << "\n";

    Pos best = start;

    for (int y = 0; y < y_dim; ++y)
        for (int x = 0; x < x_dim; ++x)
            if (grid[y][x] == 'a' && d[y][x] != -1
                && d[y][x] < d[best.y][best.x])
                best = { x, y };

    std::cout << d[best.y][best.x] << "\n";
}