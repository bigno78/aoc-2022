#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>

enum class PacketType
{
    List, Number
};

struct Packet
{
    std::vector<std::unique_ptr<Packet>> elems;
    int val;
    PacketType type;
};


int parse_packet(const std::string& s, Packet& packet, int i);
int parse_number(const std::string& s, Packet& packet, int i);
int parse_list(const std::string& s, Packet& packet, int i);


Packet parse_packet(const std::string& s)
{
    Packet p;
    parse_packet(s, p, 0);
    return p;
}

int parse_packet(const std::string& s, Packet& packet, int i)
{
    if (s[i] == '[')
        return parse_list(s, packet, i + 1);
    return parse_number(s, packet, i);
}

int parse_list(const std::string& s, Packet& packet, int i)
{
    packet.type = PacketType::List;

    while (s[i] != ']')
    {
        if (s[i] == ',')
            ++i;

        packet.elems.push_back(std::make_unique<Packet>());
        i = parse_packet(s, *packet.elems.back(), i);
    }

    return i + 1;
}

int parse_number(const std::string& s, Packet& packet, int i)
{
    packet.type = PacketType::Number;
    packet.val = 0;

    while (i < s.size() && std::isdigit(s[i]))
        packet.val = packet.val*10 + s[i++] - '0';

    return i;
}


int compare(const Packet& lhs, const Packet& rhs)
{
    if (lhs.type == PacketType::List && rhs.type == PacketType::List)
    {
        for (int i = 0; i < std::min(lhs.elems.size(), rhs.elems.size()); ++i)
        {
            auto res = compare(*lhs.elems[i], *rhs.elems[i]);
            if (res != 0)
                return res;
        }

        if (lhs.elems.size() == rhs.elems.size())
            return 0;
        if (lhs.elems.size() < rhs.elems.size())
            return -1;
        return 1;
    }

    if (lhs.type == PacketType::Number && rhs.type == PacketType::List)
    {
        if (rhs.elems.empty())
            return 1;

        auto res = compare(lhs, *rhs.elems[0]);

        if (res != 0)
            return res;
        if (rhs.elems.size() == 1)
            return 0;
        return -1;
    }

    if (lhs.type == PacketType::List && rhs.type == PacketType::Number)
        return -compare(rhs, lhs);

    return lhs.val == rhs.val
            ? 0
            : (lhs.val - rhs.val)/std::abs(lhs.val - rhs.val);
}
