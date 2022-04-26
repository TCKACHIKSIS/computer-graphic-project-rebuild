#ifndef SPLITTER_H
#define SPLITTER_H
#include <string>
#include <vector>

class Splitter
{
public:
    Splitter();
    std::vector<int> split(const std::string &need_to_split, const char &parametr);
};

#endif // SPLITTER_H
