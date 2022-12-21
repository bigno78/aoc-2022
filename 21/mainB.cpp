#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <optional>


struct Node
{
    Node* left = nullptr;
    Node* right = nullptr;

    char op_symbol = '\0';
    std::function<int64_t(int64_t, int64_t)> op;

    std::optional<int64_t> val;
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

int64_t deduce_left(char op, int64_t target, int64_t other)
{
    switch (op)
    {
        case '+': return target - other;
        case '-': return target + other;
        case '*': return target / other;
        case '/': return target * other;
    }

    assert(false);
}

int64_t deduce_right(char op, int64_t target, int64_t other)
{
    switch (op)
    {
        case '+': return target - other;
        case '-': return other - target;
        case '*': return target / other;
        case '/': return other / target;
    }

    assert(false);
}


std::optional<int64_t> partial_eval(Node* node)
{
    if (node->op)
    {
        auto left_val = partial_eval(node->left);
        auto right_val = partial_eval(node->right);

        if (left_val && right_val)
            node->val = node->op(*left_val, *right_val);
    }

    return node->val;
}


int64_t deduce(Node* node, int64_t target)
{
    if (!node->op)
        return target;

    if (!node->left->val)
    {
        auto need = deduce_left(node->op_symbol, target, *node->right->val);
        return deduce(node->left, need);
    }

    auto need = deduce_right(node->op_symbol, target, *node->left->val);
    return deduce(node->right, need);
}


int64_t solve(Node* root)
{
    partial_eval(root);

    if (!root->left->val)
        return deduce(root->left, *root->right->val);

    return deduce(root->right, *root->left->val);
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
            if (label != "humn")
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

            node.op_symbol = line[11];
            node.op = get_op(node.op_symbol);
        }
    }

    std::cout << solve(root) << "\n";
}
