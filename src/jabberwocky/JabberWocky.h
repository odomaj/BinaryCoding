
#include <string>
#include <list>

#ifndef JABBERWOCKY_H_
#define JABBERWOCKY_H_

typedef struct
{
    int index;
    std::string str;
} TableEntry_t;


class JabberWocky
{
    public:
    JabberWocky();
    std::string strToBits(const std::string& str);
    std::string bitsToStr(const std::string& bits);
    std::string jabber(const std::string& bits);
    std::string wocky(const std::string& bits);
    private:
    std::list<TableEntry_t> table;
    void initializeTable();
    std::string charToBits(char character);
    char bitsToChar(const std::string& eightBits);
    TableEntry_t* longestPrefix(const std::string& bits, int start);
    bool isPrefix(const std::string& str, const std::string& prefix);
    std::string indexToStr(int index);
    int strToIndex(const std::string& str);
    int calcLength();
    int getLastIndex();
    TableEntry_t* getEntry(int index);

};

#endif