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
    int k = 1000; // eh, should work
    std::string line;

    do
    {
        std::getline(std::cin, line);
        for (int i = 0; i < line.size(); ++i)
            seen[line[i]] = k;

        std::getline(std::cin, line);
        int max_diff = line.size();
        for (int i = 0; i < line.size(); ++i)
            seen[line[i]]++;

        std::getline(std::cin, line);
        for (int i = 0; i < line.size(); ++i)
        {
            if (seen[line[i]] >= k + 1) {
                total += priority[line[i]];
                break;
            }
        }

        // Add 3 for good measure.
        k += max_diff + 3;
    } while(std::cin);

    std::cout << total << "\n";
}
