#include <iostream>
#include <string>
#include <vector>

size_t view_distance(const std::vector<std::string>& grid,
                     int x, int y, int dx, int dy)
{
    int xx = x + dx;
    int yy = y + dy;

    size_t score = 0;
    while (0 <= xx && xx < grid[y].size() && 0 <= yy && yy < grid.size())
    {
        score++;

        if (grid[y][x] <= grid[yy][xx])
            break;

        xx += dx;
        yy += dy;
    }

    return score;
}

int main()
{
    std::vector<std::string> grid;

    std::string line;
    while (std::getline(std::cin, line))
    {
        grid.emplace_back(std::move(line));
    }

    size_t rows = grid.size();
    size_t cols = grid.front().size();

    size_t best = 0;

    for (size_t r = 0; r < rows; ++r)
    {
        for (size_t c = 0; c < cols; ++c)
        {
            size_t total_score = view_distance(grid, c, r, 0, 1)
                                * view_distance(grid, c, r, 0, -1)
                                * view_distance(grid, c, r, 1, 0)
                                * view_distance(grid, c, r, -1, 0);
            if (total_score > best)
                best = total_score;
        }
    }

    std::cout << best << "\n";
}