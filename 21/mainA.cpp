#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <map>


struct Node
{
    Node* left = nullptr;
    Node* right = nullptr;
    std::function<int64_t(int64_t, int64_t)> op;
    int64_t val = -1;
};


std::function<int64_t(int64_t, int64_t)> get_op(char op)
{
    switch (op)
    {
        case '+': return std::plus<int64_t>{};
        case '-': return std::minus<int64_t>{};
        case '*': return std::multiplies<int64_t>{};
        case '/': return std::divides<int64_t>{};
    }

    assert(false);
}


int64_t eval(Node* node)
{
    if (node->op)
        return node->op(eval(node->left), eval(node->right));
    return node->val;
}


int main()
{
    std::vector<Node> node_storage;
    node_storage.reserve(2000);

    std::map<std::string, Node*> providers;
    std::map<std::string, Node**> consumers;

    Node* root;

    std::string line;
    while (std::getline(std::cin, line))
    {
        node_storage.emplace_back();
        auto& node = node_storage.back();

        std::string label = line.substr(0, 4);

        if (label == "root")
            root = &node;

        auto it = consumers.find(label);
        if (it != consumers.end())
            *it->second = &node;
        else
            providers.insert({label, &node});

        if (std::isdigit(line[6]))
        {
            node.val = std::atoi(line.c_str() + 6);
        }
        else
        {
            std::string left = line.substr(6, 4);
            auto it = providers.find(left);
            if (it != providers.end())
                node.left = it->second;
            else
                consumers.insert({left, &node.left});

            std::string right = line.substr(13, 4);
            it = providers.find(right);
            if (it != providers.end())
                node.right = it->second;
            else
                consumers.insert({right, &node.right});

            node.op = get_op(line[11]);
        }
    }

    std::cout << eval(root) << "\n";
}
