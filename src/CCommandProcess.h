#ifndef __CCOMMANDPROCESS_H__
#define __CCOMMANDPROCESS_H__

#include <string>
#include <filesystem>

#include "CCommands.h"

using namespace std;
using namespace std::filesystem;

class CCommandProcess
{
    public:
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
        void end() const;
        void sendFileCom(const CCommand&, int) const;
        void sendDelCom(const CCommand&, int) const;
        void sendHelpCom(const CCommand&) const;
        void sendCreateCom(const CCommand&, int) const;
        void sendFileCom(const CCommand&, bool) const;
        void sendFileCom(const CCommand&, const string&) const;
        void sendFileCom(const CCommand&) const;
        bool matchRegex(const string&, const string&) const;
        string getFile(const string&) const;
        vector<string> m_Vec;
};

#endif

