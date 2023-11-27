#include "Huffman.h"

#include <sstream>

Huffman::Huffman(){}

Huffman::~Huffman(){}

std::string Huffman::encode(const std::string& message)
{
    tree = HuffmanTree_t(message.data(), message.length());
    std::ostringstream oss;
    for(int i = 0; i < message.length(); i++)
    {
        oss << tree.encodeChar(message[i]);
    }
    return oss.str();
}

std::string Huffman::decode(const std::string& bits)
{

}