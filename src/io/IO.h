
#include <string>

#ifndef IO_H_
#define IO_H_

class IO
{
    public:
    IO();
    void write(const std::string& str, const std::string& filename);
    std::string read(const std::string& filename);
};

#endif