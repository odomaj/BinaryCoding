#include "HuffmanTree.h"

HuffmanTree_t::HuffmanTree_t()
{
    root = new Node_t();
}

HuffmanTree_t::HuffmanTree_t(const char* str, int length)
{
    std::map<char, int> tree;
    for(int i = 0; i < length; i++)
    {
        if(tree.find(str[i]) == tree.end())
        {
            tree.insert({str[i], 1});
        }
        else
        {
            tree[str[i]]++;
        }
    }

    buildTree(tree);
}

HuffmanTree_t::~HuffmanTree_t()
{
    emptyTree(root);
    root = nullptr;
}

void HuffmanTree_t::buildTree(const std::map<char, int>& values)
{
    std::map<int, Node_t*> tree;
    for(auto it = values.begin(); it != values.end(); it++)
    {
        tree.insert({it -> second, new Node_t(&(it -> first), it -> second)});
    }

    while(tree.size() > 1)
    {
        Node_t* smallestNode = tree.begin() -> second;
        tree.erase(tree.begin());
        Node_t* secondSmallestNode = tree.begin() -> second;
        tree.erase(tree.begin());
        std::string str = secondSmallestNode -> str + smallestNode -> str;
        Node_t* node = new Node_t(str.data(), secondSmallestNode -> frequency + smallestNode -> frequency);
        node -> leftChild = smallestNode;
        node -> rightChild = secondSmallestNode;
        smallestNode -> parent = node;
        secondSmallestNode -> parent = node;
        tree.insert({node -> frequency, node});
    }

    root = tree.begin() -> second;
}

void HuffmanTree_t::emptyTree(Node_t* node)
{
    if(node -> leftChild != nullptr)
    {
        emptyTree(node -> leftChild);
    }
    if(node -> rightChild != nullptr)
    {
        emptyTree(node -> rightChild);
    }
    delete node;
}

std::string HuffmanTree_t::encodeChar(char c)
{
    Node_t* node = root;
    std::ostringstream oss;
    while(node -> leftChild != nullptr)
    {
        if(charInString(c, node -> leftChild -> str))
        {
            oss << '0';
            node = node -> leftChild;
        }
        else
        {
            oss << '1';
            node = node -> rightChild;
        }
    }
    return oss.str();
}

char HuffmanTree_t::decodeNext(std::istringstream& iss)
{
    Node_t* node = root;
    while(node -> leftChild != nullptr && !iss.fail())
    {
        char c = iss.get();
        if(c == '1')
        {
            node = node -> rightChild;
        }
        else
        {
            node = node -> leftChild;
        }
    }
    return node -> str[0];
}

bool HuffmanTree_t::charInString(char c, const std::string& str)
{
    for(int i = 0; i < str.length(); i++)
    {
        if(c == str[i])
        {
            return true;
        }
    }
    return false;
}

std::string HuffmanTree_t::serialize()
{
    std::ostringstream oss;
    std::map<char, std::string> keys;
    findKeys(root, "", keys);
    for(auto it = keys.begin(); it != keys.end(); it++)
    {
        oss << '[' << it -> first << "] -- " << it -> second << '\n';
    }
    return oss.str();
}

void HuffmanTree_t::deserialize(const std::string& tree)
{
    std::istringstream iss;
    std::map<char, std::string> keys;
    while(!iss.fail())
    {
        if(iss.str().empty())
        {
            return;
        }
        std::string str;
        iss >> str;
        if(str[0] != '[' || str[str.length() - 1] != ']')
        {
            return;
        }
        char key = str[1];
        iss >> str;
        iss >> str;
        keys.insert({key, str});
    }
}

void HuffmanTree_t::findKeys(Node_t* node, std::string value, std::map<char, std::string>& keys)
{
    if(node == nullptr)
    {
        return;
    }
    if((node -> str).length() == 1)
    {
        keys.insert({(node -> str)[0], value});
        return;
    }
    findKeys(node -> leftChild, value + '0', keys);
    findKeys(node -> rightChild, value + '1', keys);
}

Node_t::Node_t()
{
    parent = nullptr;
    leftChild = nullptr;
    rightChild = nullptr;
    str = "";
    frequency = 1;
}

Node_t::Node_t(const char* str_, int frequency_)
{
    parent = nullptr;
    leftChild = nullptr;
    rightChild = nullptr;
    str = std::string(str);
    frequency = frequency_;
}
