#ifndef __CPARSER_H__
#define __CPARSER_H__

#include <string>
#include <vector>

using namespace std;

class CParser
{
    public:
        CParser() = default;
        ~CParser() = default;
        CParser(const CParser& x) = delete;
        bool parseCommand(const string& input, vector<string>& output);
};

#endif