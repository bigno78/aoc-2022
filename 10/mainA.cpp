#include <iostream>
#include <string>
#include <sstream>

int main()
{
    int x = 1;
    int cycle = 1;
    int target = 20;
    int res = 0;

    std::string line;
    while (std::getline(std::cin, line))
    {
        std::stringstream ss(line);
        std::string inst;

        ss >> inst;

        int new_val = x;
        int len = 1;

        if (inst == "addx")
        {
            int arg;
            ss >> arg;

            new_val = x + arg;
            len = 2;
        }

        if (cycle + len > target)
        {
            res += target * x;
            target += 40;
        }

        x = new_val;
        cycle += len;
    }

    std::cout << res << "\n";
}
