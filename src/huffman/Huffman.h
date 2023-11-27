#include "HuffmanTree.h"

#ifndef HUFFMAN_H_
#define HUFFMAN_H_

class Huffman
{
    public:
    Huffman();
    ~Huffman();
    std::string encode(const std::string& message);
    std::string decode(const std::string& bits);
    std::string 
    private:
    HuffmanTree_t tree;
    std::string encode(const std::string& message);
    std::string decode(const std::string& bits);
};

#endif