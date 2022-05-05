#ifndef __CCOMMAND_H__
#define __CCOMMAND_H__

#include <string>

using namespace std;

class CCommand
{
    public:
        CCommand(const string& command) : m_Command(command) {}
        bool doCommand(const string& command);

    private:
        string m_Command;
};

#endif

