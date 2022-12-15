#pragma once

#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <sstream>

struct Pos
{
    int x, y;
};

static Pos normalize_dirs(Pos pos)
{
    return { pos.x == 0 ? 0 : pos.x/std::abs(pos.x),
             pos.y == 0 ? 0 : pos.y/std::abs(pos.y) };
}

std::vector<std::vector<bool>> load_grid()
{
    std::vector<std::vector<Pos>> segs;
    int w = 0;
    int h = 0;

    std::string line;
    while (std::getline(std::cin, line))
    {
        segs.emplace_back();
        Pos pos;

        std::stringstream ss(line);
        char black_hole;
        std::string the_abyss;

        while (ss)
        {
            ss >> pos.x >> black_hole >> pos.y >> the_abyss;

            segs.back().push_back(pos);

            if (pos.x + 1 > w)
                w = pos.x + 1;
            if (pos.y + 1 > h)
                h = pos.y + 1;
        }
    }

    std::vector<std::vector<bool>> grid(h, std::vector<bool>(w, false));

    for (const auto& s : segs)
    {
        Pos p = s.front();
        for (int i = 1; i < s.size(); ++i)
        {
            Pos dir = normalize_dirs({ s[i].x - p.x, s[i].y - p.y });
            while (p.x != s[i].x || p.y != s[i].y)
            {
                grid[p.y][p.x] = true;
                p.x += dir.x;
                p.y += dir.y;
            }
        }
        grid[p.y][p.x] = true;
    }

    return grid;
}
