#include <map>
#include <string>

#ifndef HUFFMANTREE_H_
#define HUFFMANTREE_H_

struct Node_t
{
    Node_t* parent;
    Node_t* leftChild;
    Node_t* rightChild;
    std::string str;
    int frequency;
    Node_t();
    Node_t(const char* str_, int frequency_);
};

class HuffmanTree_t
{
    public:
    HuffmanTree_t();
    HuffmanTree_t(const char* str, int length);
    ~HuffmanTree_t();
    private:
    Node_t* root;
    void buildTree(const std::map<char, int>& values);
    void emptyTree(Node_t* node);
};

#endif