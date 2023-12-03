#include "huffman/HuffMan.h"
#include "jabberwocky/JabberWocky.h"
#include "io/IO.h"

#include <iostream>

int main()
{
    IO io;

    JabberWocky jabberwocky;
    io.write(jabberwocky.jabber(jabberwocky.strToBits(io.read("../test/jabberwocky/text.txt"))), "../test/jabberwocky/encoding.txt");
    io.write(jabberwocky.bitsToStr(jabberwocky.wocky(io.read("../test/jabberwocky/encoding.txt"))), "../test/jabberwocky/decoding.txt");
    
    Huffman huffman;
    HuffmanOutpuf_t data;
    data.serializedTree = io.read("../test/huffman/codewords.txt");
    data.message = io.read("../test/huffman/encoding.txt"); 
    io.write(huffman.decode(data), "../test/huffman/decoding.txt");

    data = huffman.encode(io.read("../test/huffman/test2.txt"));
    io.write(data.message, "../test/huffman/encode2.txt");
    io.write(data.serializedTree, "../test/huffman/code2.txt");
    io.write(huffman.decode(data), "../test/huffman/decode2.txt");
}