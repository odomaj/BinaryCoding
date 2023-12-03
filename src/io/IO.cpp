#include "IO.h"

#include <fstream>
#include <sstream>

IO::IO(){}

void IO::write(const std::string& str, const std::string& filename)
{
    std::ofstream out;
    out.open(filename);
    out << str;
    out.close();
}

std::string IO::read(const std::string& filename)
{
    std::ifstream in;
    in.open(filename);
    std::ostringstream oss;
    std::string str;
    while(!std::getline(in, str).fail())
    {
        oss << str << '\n';
    }
    in.close();
    return oss.str().substr(0, oss.str().length()-1);
}