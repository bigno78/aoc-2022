#include <cstdio>
#include <iostream>
#include <string>

int main()
{
    int a, b, x, y;
    int includes = 0;
    int overlaps = 0;

    while(std::scanf(" %d-%d,%d-%d ", &a, &b, &x, &y) == 4)
    {
        if ((a >= x && b <= y) || (x >= a && y <= b))
        {
            includes++;
        }

        if (y >= a && x <= b) {
            overlaps++;
        }

    }

    std::cout << includes << "\n";
    std::cout << overlaps << "\n";
}