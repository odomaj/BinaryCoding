#include "huffman/HuffMan.h"
#include "jabberwocky/JabberWocky.h"
#include "io/IO.h"

#include <iostream>

int main()
{
    /*
    JabberWocky jabberwocky = JabberWocky();
    std::string test = "test";
    test = jabberwocky.strToBits(test);
    test = jabberwocky.bitsToStr(test);
    std::cout << test << '\n';

    test = "01100110111";
    std::cout << test << '\n';
    test = jabberwocky.jabber(test);
    std::cout << test << '\n';
    std::cout << jabberwocky.wocky(test);
    return 0;
    */

   Huffman huffman;
   HuffmanOutpuf_t output = huffman.encode("testing message");
   std::cout << output.message;
}