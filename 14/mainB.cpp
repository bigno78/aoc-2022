#include "grid_stuff.hpp"

#include <vector>
#include <algorithm> // max

struct StackEntry
{
    Pos p;
    int i;
};

int main()
{
    auto bottomless_grid = load_grid();

    int old_w = bottomless_grid.front().size();
    int old_h = bottomless_grid.size();

    int h = old_h + 2;
    int w = old_w + 2*h;

    std::vector<std::vector<bool>> grid;

    for (auto& row : bottomless_grid)
    {
        grid.emplace_back(w, false);
        grid.back().insert(grid.back().begin() + h,
                           row.begin(),
                           row.end());
    }

    grid.emplace_back(w, false);
    grid.emplace_back(w, true);

    int grains = 0;

    std::vector<Pos> dirs = { { 0, 1 }, { -1, 1 }, { 1, 1 } };
    std::vector<StackEntry> stack;
    StackEntry e = { { h + 500, 0 }, 0 };

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

        if (stack.empty())
            break;

        e = stack.back();
        stack.pop_back();
    }

    std::cout << grains << "\n";
}