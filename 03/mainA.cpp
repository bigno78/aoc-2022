#include <iostream>
#include <string>

int main()
{
    int seen[256] = { 0 };
    int priority[256] = { 0 };

    for (char c = 'a'; c <= 'z'; ++c)
        priority[c] = 1 + c - 'a';
    for (char c = 'A'; c <= 'Z'; ++c)
        priority[c] = 27 + c - 'A';

    int total = 0;
    int lineno = 1;
    std::string line;

    while(std::getline(std::cin, line))
    {
        for (int i = 0; i < line.size()/2; ++i)
            seen[line[i]] = lineno;

        for (int i = line.size()/2; i < line.size(); ++i)
        {
            if (seen[line[i]] == lineno) {
                total += priority[line[i]];
                break;
            }
        }

        lineno++;
    }

    std::cout << total << "\n";
}
