#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <functional>
#include <algorithm>


std::function<size_t(size_t)> make_adder(size_t x)
{
    return [x] (size_t old) { return old + x; };
}

std::function<size_t(size_t)> make_self_adder()
{
    return [] (size_t old) { return old + old; };
}

std::function<size_t(size_t)> make_multiplier(size_t x)
{
    return [x] (size_t old) { return old * x; };
}

std::function<size_t(size_t)> make_self_multiplier()
{
    return [] (size_t old) { return old * old; };
}

struct Monke
{
    std::vector<size_t> items;
    size_t modulo;
    std::function<size_t(size_t)> update_item;
    int true_monke;
    int false_monke;

    bool test_item(size_t item)
    {
        return item % modulo == 0;
    }
};

std::vector<Monke> parse_monkes()
{
    std::vector<Monke> monkes;

    char arg1[100] = { 0 };
    char arg2[100] = { 0 };

    std::string line;
    while (std::getline(std::cin, line))
    {
        monkes.emplace_back();

        size_t item;
        const char* fmt = " Starting items: %ld";
        while (std::scanf(fmt, &item) > 0)
        {
            monkes.back().items.push_back(item);
            fmt = " ,%d ";
        }

        char op;
        std::scanf(" Operation: new = %s %c %s", arg1, &op, arg2);

        if (op == '+')
        {
            monkes.back().update_item = std::string(arg2) == "old"
                                        ? make_self_adder()
                                        : make_adder(std::atoi(arg2));
        }
        else if (op == '*')
        {
            monkes.back().update_item = std::string(arg2) == "old"
                                        ? make_self_multiplier()
                                        : make_multiplier(std::atoi(arg2));
        }

        std::scanf(" Test: divisible by %ld ", &monkes.back().modulo);
        std::scanf(" If true: throw to monkey %d ", &monkes.back().true_monke);
        std::scanf(" If false: throw to monkey %d ",
                   &monkes.back().false_monke);
    }

    return monkes;
}

template<typename UpdateFunc>
size_t get_business_level(std::vector<Monke> monkes,
                       size_t rounds, UpdateFunc f)
{
    std::vector<size_t> inspections(monkes.size());

    for (size_t round = 0; round < rounds; ++round)
    {
        for (int i = 0; i < monkes.size(); ++i)
        {
            auto& monke = monkes[i];
            inspections[i] += monke.items.size();

            for (auto item : monke.items)
            {
                size_t new_worry = f(monke.update_item(item));

                if (monke.test_item(new_worry))
                    monkes[monke.true_monke].items.push_back(new_worry);
                else
                    monkes[monke.false_monke].items.push_back(new_worry);
            }

            monke.items.clear();
        }
    }

    std::sort(inspections.begin(), inspections.end());

    return inspections[inspections.size() - 1]
            * inspections[inspections.size() - 2];
}

int main()
{
    auto monkes = parse_monkes();

    size_t part_one =
        get_business_level(monkes, 20, [] (size_t worry) { return worry/3; });

    size_t m = 1;
    for (const auto& monke : monkes)
        m *= monke.modulo;

    size_t part_two =
        get_business_level(monkes, 10000, [m] (size_t worry) { return worry % m; });

    std::cout << part_one << "\n";
    std::cout << part_two << "\n";
}
