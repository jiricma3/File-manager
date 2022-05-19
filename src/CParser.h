#ifndef __CPARSER_H__
#define __CPARSER_H__

#include <string>
#include <vector>

using namespace std;

class CParser
{
    public:
        CParser() = default;
        CParser(vector <string> & vec) : m_Vec(vec) { parseCommands(); }
        CParser(const CParser& x) = delete;
        ~CParser() = default;
    
    private:
        bool parseCommands();
        void one();
        void two();
        void three();
        void four();
        void help();
        vector<string> m_Vec;
};

#endif