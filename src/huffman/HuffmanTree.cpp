#include "HuffmanTree.h"

#include <queue>

#include <iostream>
HuffmanTree_t::HuffmanTree_t(){}

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

HuffmanTree_t::~HuffmanTree_t(){}

void HuffmanTree_t::buildTree(const std::map<char, int>& values)
{
    std::priority_queue<std::pair<int, Node_t*>> nodes;
    for(auto it = values.begin(); it != values.end(); it++)
    {
        nodes.push({it -> second, new Node_t(std::string(1, it -> first), it -> second)});
    }

    while(nodes.size() > 1)
    {
        Node_t* smallestNode = nodes.top().second;
        nodes.pop();
        Node_t* secondSmallestNode = nodes.top().second;
        nodes.pop();

        std::string str = secondSmallestNode -> str + smallestNode -> str;
        Node_t* node = new Node_t(str.data(), secondSmallestNode -> frequency + smallestNode -> frequency);
        node -> leftChild = smallestNode;
        node -> rightChild = secondSmallestNode;

        smallestNode -> parent = node;
        secondSmallestNode -> parent = node;

        nodes.push({node -> frequency, node});
    }

    fillMaps(nodes.top().second, "");
    emptyTree(nodes.top().second);
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
    return charToStr[c];
}

char HuffmanTree_t::decodeNext(std::istringstream& iss)
{
    std::ostringstream oss;
    while(!iss.fail())
    {
        oss << (char)iss.get();
        auto it = strToChar.find(oss.str());
        if(it != strToChar.end())
        {
            return (it -> second);
        }
    }
    return ' ';
}

std::string HuffmanTree_t::serialize()
{
    std::ostringstream oss;
    for(auto it = charToStr.begin(); it != charToStr.end(); it++)
    {
        oss << '[' << writeEscape(it -> first) << "] -- " << it -> second << '\n';
    }
    return oss.str();
}

void HuffmanTree_t::deserialize(const std::string& tree)
{
    std::istringstream iss;
    iss.str(tree);
    while(!iss.fail())
    {
        std::string str = "";
        iss >> str;
        if(str[0] != '[')
        {
            break;
        }
        while(str[str.length() - 1] != ']')
        {
            str += iss.get();
            if(iss.fail())
            {
                return;
            }
        }
        char key = readEscape(str.substr(1, 2));
        iss >> str;
        iss >> str;
        charToStr.insert({key, str});
        strToChar.insert({str, key});
    }
}

void HuffmanTree_t::fillMaps(Node_t* node, std::string value)
{
    if(node == nullptr)
    {
        return;
    }
    if((node -> str).length() == 1)
    {
        charToStr.insert({(node -> str)[0], value});
        strToChar.insert({value, (node -> str)[0]});
        return;
    }
    fillMaps(node -> leftChild, value + '0');
    fillMaps(node -> rightChild, value + '1');
}

Node_t::Node_t()
{
    parent = nullptr;
    leftChild = nullptr;
    rightChild = nullptr;
    str = "";
    frequency = 1;
}

Node_t::Node_t(const std::string& str_, int frequency_)
{
    parent = nullptr;
    leftChild = nullptr;
    rightChild = nullptr;
    str = str_;
    frequency = frequency_;
}

std::string HuffmanTree_t::writeEscape(char c)
{
    switch (c)
    {
        case '\a':
            return "\\a";
        case '\b':
            return "\\b";
        case '\f':
            return "\\f";
        case '\n':
            return "\\n";
        case '\r':
            return "\\r";
        case '\t':
            return "\\t";
        case '\v':
            return "\\v";
        case '\'':
            return "\\\'";
        case '\"':
            return "\\\"";
        case '\?':
            return "\\\?";
        case '\\':
            return "\\\\";
        default:
            return std::string(1, c);
    }
}

char HuffmanTree_t::readEscape(std::string str)
{
    std::cout << str << '\n';
    if(str[0] != '\\')
    {
        return str[0];
    }
    switch (str[1])
    {
        case 'a':
            return '\a';
        case 'b':
            return '\b';
        case 'f':
            return '\b';
        case 'n':
            return '\n';
        case 'r':
            return '\r';
        case 't':
            return '\t';
        case 'v':
            return '\v';
        case '\'':
            return '\'';
        case '\"':
            return '\"';
        case '\?':
            return '\?';
        case '\\':
            return '\\';
        default:
            return ' ';
    }
}