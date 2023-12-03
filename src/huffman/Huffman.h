#include "HuffmanTree.h"

#ifndef HUFFMAN_H_
#define HUFFMAN_H_

typedef struct
{
    std::string message;
    std::string serializedTree;
} HuffmanOutpuf_t;


class Huffman
{
    public:
    Huffman();
    ~Huffman();
    HuffmanOutpuf_t encode(const std::string& message);
    std::string decode(const HuffmanOutpuf_t& data);
    private:
    HuffmanTree_t tree;
    std::string encode(const std::string& message, HuffmanTree_t& tree);
    std::string decode(const std::string& bits, HuffmanTree_t& tree);
};

#endif