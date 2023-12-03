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

typedef struct
{
    char c;
    int length;
} NextDecoded_t;


class HuffmanTree_t
{
    public:
    HuffmanTree_t();
    HuffmanTree_t(const char* str, int length);
    ~HuffmanTree_t();
    char encodeChar(char c);
    NextDecoded_t decodeNext(const std::string& message);
    std::string serialize();
    void deserialize(const std::string& tree);
    private:
    Node_t* root;
    void buildTree(const std::map<char, int>& values);
    void emptyTree(Node_t* node);
};

#endif