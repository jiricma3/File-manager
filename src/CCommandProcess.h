#ifndef __CCOMMANDPROCESS_H__
#define __CCOMMANDPROCESS_H__

#include <string>

#include "CCommands.h"

using namespace std;

class CCommandProcess
{
    public:
        CCommandProcess(int params, const string& command, const string& option, const string& from, const string& to)
        : m_NumOfParams(params), m_Command(command), m_Option(option), m_From(from), m_To(to) { processCommand(); }
        CCommandProcess(const string& id, const string& command, const string& option, const string& from, const string& to)
        : m_Id(id), m_Command(command), m_Option(option), m_From(from), m_To(to) { processCommand(); }
        CCommandProcess(int params, const string& command, const string& option, const string& from)
        : m_NumOfParams(params), m_Command(command), m_Option(option), m_From(from) { processCommand(); }
        CCommandProcess(int params, const string& command, const string& option)
        : m_NumOfParams(params), m_Command(command), m_Option(option) { processCommand(); }
        CCommandProcess(int params, const string& command)
        : m_NumOfParams(params), m_Command(command) { processCommand(); }
        CCommandProcess(vector<string>& vec) : m_Vec(vec) { processCommand(); }

    private:
        void getCom(int i) const;
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
        void sendFileCom(const CCommand&, int) const;
        void sendCreateCom(const CCommand&, int) const;
        void sendListCom(const CCommand&, bool) const;
        void sendFsCom(const CCommand&, const string&) const;
        void sendCom(const CCommand&) const;
        int m_NumOfParams = -1;
        string m_Id;
        string m_Command;
        string m_Option;
        string m_From;
        string m_To;
        vector<string> m_Vec;
};

#endif

