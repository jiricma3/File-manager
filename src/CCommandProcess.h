#ifndef __CCOMMANDPROCESS_H__
#define __CCOMMANDPROCESS_H__

#include <string>

#include "CCommands.h"

using namespace std;

class CCommandProcess
{
    public:
        CCommandProcess(const string& command, const string& option = "h", const string& from = "", const string& to = "")
        : m_Command(command), m_Option(option), m_From(from), m_To(to) { processCommand(); }

    private:
        int getOption() const;
        void processCommand() const;
        void create() const;
        void copy() const;
        void move() const;
        void del() const;
        void print() const;
        void media() const;
        void list() const;
        void change() const;
        void help() const;
        string m_Command;
        string m_Option;
        string m_From;
        string m_To;
};

#endif

