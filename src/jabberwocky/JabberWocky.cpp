#include "JabberWocky.h"

#include <sstream>
#include <iostream>
#include <cmath>

JabberWocky::JabberWocky()
{

}

void JabberWocky::initializeTable()
{
    table.clear();
    TableEntry_t entry;
    entry.index = 0;
    entry.str = "";
    table.push_back(entry);
}

std::string JabberWocky::strToBits(const std::string& str)
{
    std::ostringstream oss;
    for(int i = 0; i < str.length(); i++)
    {
        oss << charToBits(str[i]);
    }
    return oss.str();
}

std::string JabberWocky::bitsToStr(const std::string& bits)
{
    std::ostringstream oss;
    if(bits.length() % 8)
    {
        return "";
    }
    for(int i = 0; i < bits.length(); i+=8)
    {
        oss << bitsToChar(bits.substr(i, 8));
    }
    return oss.str();
}

std::string JabberWocky::jabber(const std::string& bits)
{
    initializeTable();
    std::ostringstream oss;
    int i = 0;
    while(i < bits.length())
    {
        TableEntry_t newEntry;
        newEntry.index = getLastIndex() + 1;

        TableEntry_t* prefix = longestPrefix(bits, i);
        i += (prefix -> str).length();

        newEntry.str = prefix -> str;
        oss << indexToStr(prefix -> index);

        table.push_back(newEntry);
        auto entry = table.end();
        entry--;

        if(i < bits.length())
        {
            oss << bits[i];
            entry -> str += bits[i++];
        }
    }
    return oss.str();
}

std::string JabberWocky::wocky(const std::string& bits)
{
    initializeTable();
    std::ostringstream oss;
    int i = 0;
    while(i < bits.length())
    {
        TableEntry_t newEntry;
        newEntry.index = getLastIndex() + 1;

        newEntry.str = getEntry(strToIndex(bits.substr(i))) -> str;
        oss << newEntry.str;

        i += calcLength();

        table.push_back(newEntry);
        auto entry = table.end();
        entry--;

        if(i < bits.length())
        {
            oss << bits[i];
            entry -> str += bits[i++];
        }
    }
    return oss.str();
}

std::string JabberWocky::charToBits(char character)
{
    std::ostringstream oss;
    for(int i = 7; i > 0; i--)
    {
        if(character >> i & 1)
        {
            oss << '1';
        }
        else
        {
            oss << '0';
        }
    }
    if(character & 1)
    {
        oss << '1';
    }
    else
    {
        oss << '0';
    }
    return oss.str();
}

char JabberWocky::bitsToChar(const std::string& eightBits)
{
    char c = eightBits[7] - '0';
    for(int i = 7; i > 0; i--)
    {
        c |= (eightBits[7-i] - '0') << i;
    }
    return c;
}

TableEntry_t* JabberWocky::longestPrefix(const std::string& bits, int start)
{
    TableEntry_t* longest = &*table.begin();
    for(auto it = table.begin(); it != table.end(); it++)
    {
        if(((it -> str).length() > (longest -> str).length()) && isPrefix(bits.substr(start), it -> str))
        {
            longest = &*it;
        }
    }
    return longest;
}

bool JabberWocky::isPrefix(const std::string& str, const std::string& prefix)
{
    for(int i = 0; i< prefix.length(); i++)
    {
        if(i >= str.length())
        {
            return false;
        }
        if(str[i] != prefix[i])
        {
            return false;
        }
    }
    return true;
}

std::string JabberWocky::indexToStr(int index)
{
    std::ostringstream oss;
    for(int i = calcLength() - 1; i >= 0; i--)
    {
        oss << (char)((((unsigned)index >> i) & 1) + '0');
    }
    return oss.str();
}

int JabberWocky::strToIndex(const std::string& str)
{
    int length = calcLength() - 1;
    if(length < 0)
    {
        return 0;
    }
    int index = (int)str[length] - '0';
    for(int i = length; i > 0; i--)
    {
        index |= (str[length-i] - '0') << i;
    }
    return index;
}

int JabberWocky::calcLength()
{
    int lastIndex = getLastIndex();
    if(lastIndex == 0)
    {
        return 0;
    }
    return ((int)log2(lastIndex)) + 1;
}

int JabberWocky::getLastIndex()
{
    auto it = table.end();
    it--;
    return it -> index;
}

TableEntry_t* JabberWocky::getEntry(int index)
{
    for(auto it = table.begin(); it != table.end(); it++)
    {
        if(it -> index == index)
        {
            return &*it;
        }
    }
    return &*table.end();
}