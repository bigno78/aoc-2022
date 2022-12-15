#include "packet_stuff.hpp"

#include <iostream>
#include <string>

int main()
{
    int i = 1;
    int idx_sum = 0;

    std::string line;
    while(std::cin)
    {
        std::getline(std::cin, line);
        auto packet1 = parse_packet(line);

        std::getline(std::cin, line);
        auto packet2 = parse_packet(line);

        if (compare(packet1, packet2) == -1)
            idx_sum += i;

        std::getline(std::cin, line);
        ++i;
    }

    std::cout << idx_sum << "\n";
}
