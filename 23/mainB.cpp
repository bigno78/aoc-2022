#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <tuple>
#include <vector>
#include <limits>

std::vector<std::pair<int, int>> dirs_to_check(int dx, int dy)
{
    if (dx == 0 && dy != 0)
        return { { 1, dy }, { -1, dy }, { dx, dy } };
    if (dx != 0 && dy == 0)
        return { { dx, 1 }, { dx, -1 }, { dx, dy } };

    assert(false);
}

void print(const std::set<std::pair<int, int>>& map)
{
    int big_enough = std::numeric_limits<int>::max();
    int small_enough = std::numeric_limits<int>::min();

    int min_x = big_enough, max_x = small_enough;
    int min_y = big_enough, max_y = small_enough;

    for (auto [ x, y ] : map)
    {
        max_x = std::max(max_x, x);
        min_x = std::min(min_x, x);

        max_y = std::max(max_y, y);
        min_y = std::min(min_y, y);
    }

    int hits = 0;

    for (int y = min_y; y <= max_y; ++y)
    {
        for (int x = min_x; x <= max_x; ++x)
        {
            if (map.count({x, y}) > 0)
            {
                std::cout << "#";
                hits++;
            }
            else
                std::cout << ".";
        }
        std::cout << "\n";
    }
    std::cout << "--------------------------\n";

    if (hits != map.size())
        std::cout << "BAD HITS: " << hits << " vs " << map.size() << "!!!!!!!!1\n";
}

int main()
{
    std::pair<int, int> straight_dirs[4] =
            { { 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 } };
    char dir_chars[4] = { 'N', 'S', 'W', 'E' };

    std::set<std::pair<int, int>> map;

    int init_size = 0;
    int y = 0;
    std::string line;
    while (std::getline(std::cin, line))
    {
        for (int x = 0; x < line.size(); ++x)
        {
            if (line[x] == '#')
            {
                map.insert({ x, y });
                ++init_size;
            }
        }
        ++y;
    }

    print(map);

    int round = 0;
    while (true)
    {
        std::map<std::pair<int, int>, int> propositions;
        std::vector<std::pair<int, int>> pos;
        std::vector<std::pair<int, int>> proposed_pos;

        std::set<std::pair<int, int>> new_map;

        for (auto [ x, y ] : map)
        {
            int invalid = 5684655;
            int nx = invalid, ny = invalid;
            int clear_dirs = 0;

            //std::cout << "Doing " << x << " " << y << "\n";

            for (int i = 0; i < 4; ++i)
            {
                auto dir = straight_dirs[(round + i) % 4];

                //std::cout << "    dir " << dir.first << " " << dir.second;

                bool blocked = false;
                for (auto [ dx, dy ] : dirs_to_check(dir.first, dir.second))
                    if (map.count({ x + dx, y + dy }) > 0)
                        blocked = true;

                if (blocked)
                {
                    //std::cout << " bad\n";
                    continue;
                }

                clear_dirs++;
                if (clear_dirs == 1)
                {
                    //std::cout << "gud" << "\n";
                    nx = x + dir.first;
                    ny = y + dir.second;
                }
            }

            if (clear_dirs > 0 && clear_dirs < 4)
            {
                if (nx == invalid || ny == invalid)
                {
                    std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa\n";
                }
                //std::cout << "proposing " << nx << " " << ny << "\n";
                propositions[{ nx, ny }]++;
                pos.push_back({ x, y });
                proposed_pos.push_back({ nx, ny });
            }
            else
            {
                new_map.insert({x, y});
            }
        }

        if (pos.size() == 0)
        {
            break;
        }

        if (pos.size() != proposed_pos.size())
        {
            std::cout << "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n";
        }

        for (int i = 0; i < pos.size(); ++i)
        {
            if (propositions[proposed_pos[i]] < 1)
                std::cout << "wtfffffffffff\n";
            if (propositions[proposed_pos[i]] > 1)
                new_map.insert(pos[i]);
            else
                new_map.insert(proposed_pos[i]);
        }

        map = new_map;

        //print(map);

        round++;
    }

    std::cout << round + 1 << "\n";
}
