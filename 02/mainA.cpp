#include <iostream>
#include <string>

bool first_wins(char a, char b)
{
    return (a == 'C' && b == 'B')
            || (a == 'B' && b == 'A')
            || (a == 'A' && b == 'C');
}

int main()
{
    std::string line;
    int total_score = 0;

    while(std::getline(std::cin, line))
    {
        char a = line[0];
        char b = line[2] - 'X' + 'A';

        total_score += b - 'A' + 1;

        if (first_wins(b, a))
        {
            total_score += 6;
        }
        else if (!first_wins(a, b))
        {
            total_score += 3;
        }
    }

    std::cout << total_score << "\n";
}