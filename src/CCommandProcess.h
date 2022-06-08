#ifndef __CCOMMANDPROCESS_H__
#define __CCOMMANDPROCESS_H__

#include <string>
#include <filesystem>

#include "CCommands.h"

using namespace std;
using namespace std::filesystem;

/**
 * @brief Processing and parsing incoming commands.
 * 
 * This class gets a vector of arguments from standard input, processes it and calls the required command.
 */
class CCommandProcess
{
    public:
        CCommandProcess() = default;
        ~CCommandProcess() = default;
        void passCommand(vector<string>&);

    private:
        void getCom(int) const;
        int getOption() const;
        void processCommand();
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
        void current() const;
        void write() const;
        void sendFileCom(const CCommand&, int) const;
        void sendDelCom(const CCommand&, int) const;
        void sendHelpCom(const CCommand&) const;
        void sendCreateCom(const CCommand&, int) const;
        void sendFileCom(const CCommand&, bool) const;
        void sendFileCom(const CCommand&, const string&) const;
        void sendFileCom(const CCommand&) const;
        void sendWriteCom(const CCommand&, const string&, const string&) const;
        bool matchRegex(const string&, const string&) const;
        string getFile(const string&, int) const;
        vector<string> m_Vec; ///< Vector containing command arguments.
};

#endif

