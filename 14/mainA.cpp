#include "grid_stuff.hpp"

#include <vector>

struct StackEntry
{
    Pos p;
    int i;
};

int main()
{
    auto grid = load_grid();

    int w = grid.front().size();
    int h = grid.size();

    int grains = 0;

    std::vector<Pos> dirs = { { 0, 1 }, { -1, 1 }, { 1, 1 } };
    std::vector<StackEntry> stack;
    StackEntry e = { { 500, 0 }, 0 };

    while (0 <= e.p.x && e.p.x < w && 0 <= e.p.y && e.p.y < h)
    {
        if (grid[e.p.y][e.p.x])
        {
            e = stack.back();
            stack.pop_back();
            continue;
        }

        if (e.i < dirs.size())
        {
            Pos next = { e.p.x + dirs[e.i].x, e.p.y + dirs[e.i].y };
            stack.push_back({ e.p, e.i + 1 });
            e = { next, 0 };
            continue;
        }

        grid[e.p.y][e.p.x] = true;
        grains++;

        e = stack.back();
        stack.pop_back();
    }

    std::cout << grains << "\n";
}
