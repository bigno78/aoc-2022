#include <iostream>
#include <string>
#include <sstream>
#include <cmath> // abs

struct Instruction
{
    int remaining_ticks;
    int arg;

    static Instruction noop() { return { 1, 0 }; }
    static Instruction addx(int arg) { return { 2, arg }; }
};

Instruction next_inst()
{
    std::string line;

    if (!std::getline(std::cin, line))
        return Instruction::noop();

    std::stringstream ss(line);

    std::string inst;
    ss >> inst;

    if (inst == "addx") {
        int arg;
        ss >> arg;

        return Instruction::addx(arg);
    }

    return Instruction::noop();
}

int main()
{
    Instruction curr_inst = next_inst();
    int x = 1;

    for (int r = 0; r < 6; ++r)
    {
        for (int c = 0; c < 40; ++c)
        {
            if (curr_inst.remaining_ticks == 0)
            {
                x += curr_inst.arg;
                curr_inst = next_inst();
            }

            if (std::abs(c - x) < 2)
                std::cout << "#";
            else
                std::cout << ".";

            curr_inst.remaining_ticks--;
        }
        std::cout << "\n";
    }
}
