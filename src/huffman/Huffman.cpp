#include "Huffman.h"

#include <sstream>

Huffman::Huffman(){}

Huffman::~Huffman(){}

HuffmanOutpuf_t Huffman::encode(const std::string& message)
{
    HuffmanOutpuf_t output;
    HuffmanTree_t tree = HuffmanTree_t(message.data(), message.length());
    output.message = encode(message, tree);
    output.serializedTree = tree.serialize();
    return output;
}

std::string Huffman::decode(const HuffmanOutpuf_t& data)
{
    HuffmanTree_t tree;
    tree.deserialize(data.serializedTree);
    return decode(data.message, tree);
}

std::string Huffman::encode(const std::string& message, const HuffmanTree_t& tree)
{
    std::ostringstream oss;
    for(int i = 0; i < message.length(); i++)
    {
        oss << tree.encodeChar(message[i]);
    }
    return oss.str();
}

std::string Huffman::decode(const std::string& message, const HuffmanTree_t& tree)
{
    int i = 0;
    std::ostringstream oss;
    while(i < message.length())
    {
        NextDecoded_t next = tree.decodeNext(message.substr(i));
        i += next.length;
        oss << next.c;
    }
    return oss.str();
}