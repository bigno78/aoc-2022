#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    char smallest = '0' - 1;

    std::vector<std::string> col_maxes;
    std::vector<std::string> row_maxes;
    std::vector<std::string> lowest_cover;

    std::vector<std::string> grid;

    std::string line;
    std::getline(std::cin, line);

    row_maxes.emplace_back(line.size() + 2, smallest);
    col_maxes.emplace_back(line.size() + 2, smallest);

    do
    {
        col_maxes.emplace_back(line.size() + 2, smallest);
        row_maxes.emplace_back(line.size() + 2, smallest);
        lowest_cover.emplace_back(line.size() + 2, smallest);

        auto& prev_cols = *(col_maxes.end() - 2);
        auto& curr_cols = col_maxes.back();
        auto& curr_row = row_maxes.back();

        for (size_t i = 0; i < line.size(); ++i)
        {
            curr_cols[i + 1] = std::max(line[i], prev_cols[i + 1]);
            curr_row[i + 1] = std::max(line[i], curr_row[i]);
            lowest_cover.back()[i] = std::max(prev_cols[i + 1], curr_row[i]);
        }

        grid.push_back(std::move(line));
    } while (std::getline(std::cin, line));

    size_t rows = grid.size();
    size_t cols = grid.front().size();
    size_t res = 0;

    std::string bottom_maxes(cols, smallest);
    for (int row = rows - 1; row >= 0; --row)
    {
        char right_max = smallest;
        for (int col = cols - 1; col >= 0; --col)
        {
            auto h = grid[row][col];
            if (h > right_max
                || h > bottom_maxes[col]
                || h > row_maxes[row + 1][col]
                || h > col_maxes[row][col + 1])
            {
                res++;
            }

            right_max = std::max(right_max, h);
            bottom_maxes[col] = std::max(bottom_maxes[col], h);
        }
    }

    std::cout << res << "\n";
}