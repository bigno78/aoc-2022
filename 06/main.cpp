#include <iostream>
#include <string>

int find_marker(const std::string& datastream, int length)
{
    int map[26] = { 0 };
    int count = 0;

    for (int i = 0; i < 26; ++i) map[i] = -69;

    for (int i = 0; i < datastream.size(); ++i)
    {
        int last_occurrence = map[datastream[i] - 'a'];

        if (last_occurrence < i - count)
        {
            if (++count == length)
            {
                return i + 1;
            }
        }
        else
        {
            count = i - last_occurrence;
        }

        map[datastream[i] - 'a'] = i;
    }

    return -1;
}

int main()
{
    std::string datastream;
    std::cin >> datastream;

    std::cout << find_marker(datastream, 4) << "\n";
    std::cout << find_marker(datastream, 14) << "\n";
}