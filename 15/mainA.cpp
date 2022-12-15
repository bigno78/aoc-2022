#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <unordered_set>

int main()
{
    std::vector<int> xs, bacon_xs;
    std::vector<int> ys, bacon_ys;
    std::vector<int> ds;

    std::string line;
    while (std::getline(std::cin, line))
    {
        int sensor_x, sensor_y;
        int bacon_x, bacon_y;

        std::sscanf(line.c_str(),
                    "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d",
                    &sensor_x, &sensor_y, &bacon_x, &bacon_y);

        xs.push_back(sensor_x);
        ys.push_back(sensor_y);
        bacon_xs.push_back(bacon_x);
        bacon_ys.push_back(bacon_y);
        ds.push_back(std::abs(bacon_x - sensor_x)
                    + std::abs(bacon_y - sensor_y));
    }

    int row = 2000000;

    std::vector<int> froms(xs.size());
    std::vector<int> tos(xs.size());
    std::vector<int> indices(xs.size());

    for (int i = 0; i < xs.size(); ++i)
    {
        indices[i] = i;

        int radius = ds[i] - std::abs(row - ys[i]);

        if (radius < 0)
            continue;

        froms[i] = xs[i] - radius;
        tos[i] = xs[i] + radius;
    }

    std::sort(indices.begin(), indices.end(),
            [&] (int i, int j)
            {
                return froms[i] < froms[j];
            });

    int total = 0;
    int end = froms[indices[0]];
    std::unordered_set<int> banned_xs;

    for (int i = 0; i < froms.size(); ++i)
    {
        int idx = indices[i];
        int from = std::max(end, froms[idx]);

        if (from <= tos[idx])
        {
            total += tos[idx] - from + 1;
            end = tos[idx] + 1;
        }

        if (bacon_ys[idx] == row)
            banned_xs.insert(bacon_xs[idx]);
    }

    std::cout << total - banned_xs.size() << "\n";
}
