#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

struct Dir
{
    Dir* parent;
    std::map<std::string, Dir*> subdirs;

    size_t file_size = 0;
    size_t size = 0;
};

Dir* push_dir(std::vector<Dir>& dir_buffer, Dir* parent)
{
    dir_buffer.emplace_back();
    Dir* dir = &dir_buffer.back();

    dir->parent = parent;

    return dir;
}

bool starts_with(const std::string& s, const std::string& prefix)
{
    return s.rfind(prefix, 0) == 0;
}

void calc_sizes(Dir* current)
{
    current->size = current->file_size;

    for (const auto& [ name, child ] : current->subdirs)
    {
        calc_sizes(child);
        current->size += child->size;
    }
}

void solve(Dir* current, size_t need_to_remove, size_t& sum, size_t& removed_size)
{
    if (current->size < 100000)
        sum += current->size;

    if (current->size >= need_to_remove && current->size < removed_size)
       removed_size = current->size;

    for (const auto& [ name, child ] : current->subdirs)
    {
        solve(child, need_to_remove, sum, removed_size);
    }
}

int main()
{
    std::vector<Dir> dir_buffer;
    dir_buffer.reserve(1000);

    Dir* root = push_dir(dir_buffer, nullptr);
    Dir* current = root;

    std::string line;
    while (std::getline(std::cin, line))
    {
        std::stringstream ss(line);

        if (line[0] == '$')
        {
            std::string cmd;
            ss >> cmd >> cmd;
            if (cmd == "cd")
            {
                std::string arg;
                ss >> arg;

                if (arg == "..")
                    current = current->parent;
                else if (arg == "/")
                    current = root;
                else
                    current = current->subdirs[arg];
            }
        }
        else
        {
            if (starts_with(line, "dir"))
            {
                std::string name;
                ss >> name >> name;
                current->subdirs[name] = push_dir(dir_buffer, current);
            }
            else
            {
                size_t size;
                ss >> size;
                current->file_size += size;
            }
        }
    }

    calc_sizes(root);

    size_t need = 30000000 - (70000000 - root->size);

    size_t sum = 0;
    size_t to_remove = -1;

    solve(root, need, sum, to_remove);

    std::cout << sum << "\n";
    std::cout << to_remove << "\n";
}