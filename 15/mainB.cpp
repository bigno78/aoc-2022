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
    int limit = 4000000;

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

    std::vector<int> froms;
    std::vector<int> tos;
    std::vector<int> indices;

    for (int row = 0; row < limit; ++row)
    {
        for (int i = 0; i < xs.size(); ++i)
        {
            int radius = ds[i] - std::abs(row - ys[i]);

            if (radius < 0)
                continue;

            indices.push_back(indices.size());
            froms.push_back(xs[i] - radius);
            tos.push_back(xs[i] + radius);
        }

        std::sort(indices.begin(), indices.end(),
                [&] (int i, int j)
                {
                    return froms[i] < froms[j];
                });

        int end = -1;

        for (int i = 0; i < froms.size(); ++i)
        {
            int idx = indices[i];

            if (froms[idx] > end + 1)
            {
                std::cout << "Got it: " << end + 1 << " " << row
                          << " -> "  << size_t(end + 1)*4000000 + size_t(row)
                          << "\n";
                return 0;
            }

            end = std::max(end, tos[idx]);
        }

        froms.clear();
        tos.clear();
        indices.clear();
    }
}
