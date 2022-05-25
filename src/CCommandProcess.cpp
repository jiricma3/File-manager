#include <map>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include "CCommandProcess.h"

using namespace std;

enum code
{
    UNDEFINED,
    CREATE,
    COPY,
    MOVE,
    DELETE,
    LIST,
    MEDIA,
    CHANGE,
    PRINT,
    HELP,
    END
};

enum opt
{
    UN,
    RF,
    RD,
    RL,
    F,
    D,
    L,
    LL,
    H
};

map<string, code> coms;
map<string, opt> opts;
vector<string> vec;

void initCom()
{
    vec.push_back("create");
    vec.push_back("copy");
    vec.push_back("move");
    vec.push_back("delete");
    vec.push_back("print");
    vec.push_back("list");
    vec.push_back("change");
    vec.push_back("media");
    vec.push_back("help");
    vec.push_back("end");
}

void initOpt()
{
    opts["-rf"] = RF;
    opts["-rd"] = RD;
    opts["-rl"] = RL;
    opts["-f"] = F;
    opts["-d"] = D;
    opts["-l"] = L;
    opts["-ll"] = LL;
    opts["-h"] = H;
}

int CCommandProcess::getOption() const
{
    initOpt();

    if(m_Vec.size() < 2)
    {
        return -1;
    }

    switch(opts[m_Vec[1]])
    {
        case RF:
                return 0;
            
        case RD:
                return 1;
            
        case RL:
                return 2;
            
        case F:
                return 3;
            
        case D:
                return 4;
            
        case L:
                return 5;

        case H:
                return 6;
        
        case UN:
                return 6;

        default:
                return 6;
    }
}

void CCommandProcess::create() const
{   
    sendCreateCom(CCreate(), getOption());
}

void CCommandProcess::copy() const
{
    sendFileCom(CCopy(), getOption());
}

void CCommandProcess::move() const
{
    sendFileCom(CMove(), getOption());
}

void CCommandProcess::del() const
{
    sendDelCom(CDelete());
}

void CCommandProcess::print() const
{
    sendFileCom(CPrint(), m_Vec[1]);
}

void CCommandProcess::list() const
{
    sendFileCom(CList(), getOption() == 5 ? true : false);
}

void CCommandProcess::change() const
{
    sendFileCom(CChange(), m_Vec[1]);
}

void CCommandProcess::media() const
{
    sendFileCom(CMedia());
}

void CCommandProcess::help() const
{
    sendHelpCom(CHelp());
}

void CCommandProcess::sendCreateCom(const CCommand& c, int res) const
{
    if(res == 0 || res == 3) m_Vec.size() == 3 ? c.doCom(CFile(m_Vec[2])) : sendHelpCom(CHelp());
    if(res == 1 || res == 4) m_Vec.size() == 3 ? c.doCom(CDir(m_Vec[2])) : sendHelpCom(CHelp());
    if(res == 2 || res == 5) m_Vec.size() == 4 ? c.doCom(CLink(m_Vec[2], m_Vec[3])) : sendHelpCom(CHelp());
    if(res < 0 || res > 5) sendHelpCom(CHelp());
}

string CCommandProcess::getFile() const
{
    CFileSystem fs;
    string toFind = m_Vec[1];
    struct stat info;

    if(access(m_Vec[1].c_str(), F_OK) == 0)
    {
        toFind = realpath(m_Vec[1].c_str(), nullptr);
    }

    if(lstat(m_Vec[1].c_str(), &info) == 0)
    {
        // get absolute path to symlink todo
    }

    if(m_Vec[1].find("/") != string::npos)
    {
        string name = m_Vec[1];
        string toErase = m_Vec[1].substr(m_Vec[1].find_last_of("/\\") + 1);
        name = name.erase(name.find(toErase), toErase.length());
        fs.loadFiles(name);
    }

    return toFind;
}

void CCommandProcess::sendFileCom(const CCommand& c, int res) const
{
    CFileSystem fs;

    if(res < 0 || m_Vec.size() != 3)
    {
        sendHelpCom(CHelp());
        return;
    }

    string toFind = getFile();
    
    for(const auto& it : fs.getVector())
    {
        if(it->getFileName().compare(toFind) == 0)
        {
            c.doCom(*it, toFind, m_Vec[2]);
            break;
        }
    }
}

void CCommandProcess::sendFileCom(const CCommand& c, bool l) const
{
    if((m_Vec.size() != 1 && l == false) || (m_Vec.size() != 2 && l == true))
    {
        sendHelpCom(CHelp());
        return;
    }

    c.doCom(l);
}

void CCommandProcess::sendFileCom(const CCommand& c) const
{
    if(m_Vec.size() != 1)
    {
        sendHelpCom(CHelp());
        return;
    }

    c.doCom();
}

void CCommandProcess::sendFileCom(const CCommand& c, const string& src) const
{
    if(m_Vec.size() != 2)
    {
        sendHelpCom(CHelp());
        return;
    }

    c.doCom(src);
}

void CCommandProcess::sendDelCom(const CCommand& c) const
{
    CFileSystem fs;

    if(m_Vec.size() != 2)
    {
        sendHelpCom(CHelp());
        return;
    }
    
    string toFind = getFile();
    
    for(const auto& it : fs.getVector())
    {
        if(it->getFileName().compare(toFind) == 0)
        {
            c.doCom(*it, toFind);
            break;
        }
    }
}

void CCommandProcess::sendHelpCom(const CCommand& c) const
{
    c.doCom();
}

void CCommandProcess::getCom(int i) const
{
    switch (i)
    {
    case 0:
            create();
        break;

    case 1:
            copy();
        break;

    case 2:
            move();
        break;

    case 3:
            del();
        break;

    case 4:
            print();
        break;

    case 5:
            list();
        break;

    case 6:
            change();
        break;

    case 7:
            media();
        break;

    case 8:
            help();
        break;

    case 9:
            exit(EXIT_SUCCESS);
        break;
    
    default:
            help();
        break;
    }
}

void CCommandProcess::processCommand() const
{
    initCom();
    int i = 0;

    if(m_Vec.empty())
    {
        return;
    }

    for(const auto& it : vec)
    {
        if(it.compare(m_Vec[0]) == 0)
        {
            getCom(i);
            return;
        }

        i++;
    }

    getCom(8);
}