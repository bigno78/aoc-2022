#include <iostream>
#include <string>

int main()
{
    std::string line;
    int total_score = 0;

    int score_table[3][3] = {
        { 3, 1, 2 },
        { 1 + 3, 2 + 3, 3 + 3 },
        { 2 + 6, 3 + 6, 1 + 6 }
    };

    while(std::getline(std::cin, line))
    {
        char a = line[0];
        char b = line[2];
        total_score += score_table[b - 'X'][a - 'A'];
    }

    std::cout << total_score << "\n";
}