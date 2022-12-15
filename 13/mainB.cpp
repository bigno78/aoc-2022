#include "packet_stuff.hpp"

#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<Packet> packets;

    std::string line;
    while(std::cin)
    {
        std::getline(std::cin, line);
        packets.push_back(parse_packet(line));

        std::getline(std::cin, line);
        packets.push_back(parse_packet(line));

        std::getline(std::cin, line);
    }

    packets.push_back( parse_packet("[[2]]") );
    packets.push_back( parse_packet("[[6]]") );

    std::sort(packets.begin(), packets.end(),
                [] (const auto& p1, const auto& p2) {
                    return compare(p1, p2) == -1;
                });

    auto div1 = parse_packet("[[2]]");
    auto div2 = parse_packet("[[6]]");
    int key = 1;

    for (int i = 0; i < packets.size(); ++i)
        if (compare(packets[i], div1) == 0 || compare(packets[i], div2) == 0)
            key *= i + 1;

    std::cout << key << "\n";
}