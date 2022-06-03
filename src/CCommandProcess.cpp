#include <map>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include "CCommandProcess.h"

using namespace std;

ExTxt extxt;

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
    END,
    CURRENT
};

enum opt
{
    UN,
    R,
    F,
    D,
    L
};

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
    vec.push_back("current");
    vec.push_back("write");
}

void initOpt()
{
    opts["-r"] = R;
    opts["-f"] = F;
    opts["-d"] = D;
    opts["-l"] = L;
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
        case R:
                return 1;
            
        case F:
                return 2;
            
        case D:
                return 3;
            
        case L:
                return 4;
        
        case UN:
                return 5;

        default:
                return 5;
    }
}

bool CCommandProcess::matchRegex(const string& expression, const string& str) const
{
    regex reg (expression);
    smatch match;

    if(regex_search(str, match, reg))
    {
        return true;
    }

    return false;
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
    sendDelCom(CDelete(), getOption());
}

void CCommandProcess::print() const
{
    sendFileCom(CPrint(), m_Vec[1]);
}

void CCommandProcess::list() const
{
    sendFileCom(CList(), getOption() == 4 ? true : false);
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

void CCommandProcess::end() const
{
    throw runtime_error("exit");
}

void CCommandProcess::current() const
{
    sendHelpCom(CCurrent());
}

void CCommandProcess::write() const
{
    sendWriteCom(CWrite(), m_Vec[1], m_Vec[2]);
}

void CCommandProcess::sendCreateCom(const CCommand& c, int res) const
{
    if(res == 2) m_Vec.size() == 3 ? c.doCom(CFile(m_Vec[2])) : sendHelpCom(CHelp());
    if(res == 3) m_Vec.size() == 3 ? c.doCom(CDir(m_Vec[2])) : sendHelpCom(CHelp());
    if(res == 4) m_Vec.size() == 4 ? c.doCom(CLink(m_Vec[2], m_Vec[3])) : sendHelpCom(CHelp());
    if(res < 0 || res > 4) sendHelpCom(CHelp());
}

string CCommandProcess::getFile(const string& file, int cnt) const
{
    CFileSystem fs;
    string path = absolute(file);

    if(file.find("/") != string::npos && cnt == 0)
    {
        string name = file;
        auto toErasePos = file.find_last_of("/\\");
        string toErase = file.substr(toErasePos + 1);
        auto pos = name.find(toErase, toErasePos);
        auto len = toErase.length();
        name = name.erase(pos, len);
        fs.loadFiles(name);
    }

    return path;
}

void CCommandProcess::sendFileCom(const CCommand& c, int res) const
{
    CFileSystem fs;
    bool reg;
    bool found = false;

    if(res == -1 || (res == 1 && m_Vec.size() != 4) || (res == 5 && m_Vec.size() != 3))
    {
        sendHelpCom(CHelp());
        return;
    }

    if(res == 1)
    {
        reg = true;
    }
    else
    {
        reg = false;
    }

    if(reg)
    {
        int i = 0;

        for(const auto& it : fs.getVector()) 
        {
            string toFind = getFile(it->getFileName(), i++);

            if(matchRegex(m_Vec[2], toFind))
            {
                c.doCom(*it, m_Vec[3]);
                found = true;
            }
        }
    }
    else
    {
        string toFind = getFile(m_Vec[1], 0);

        for(const auto& it : fs.getVector())
        {
            if(it->getFileName().compare(toFind) == 0)
            {
                c.doCom(*it, m_Vec[2]);
                found = true;
                break;
            }
        }
    }

    if(!found)
    {
        throw CExeption(extxt.DoesntExist);
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

void CCommandProcess::sendDelCom(const CCommand& c, int res) const
{
    CFileSystem fs;
    bool reg;
    bool found = false;

    if(res == -1 || (res == 1 && m_Vec.size() != 3) || (res == 5 && m_Vec.size() != 2))
    {
        sendHelpCom(CHelp());
        return;
    }

    if(res == 1)
    {
        reg = true;
    }
    else
    {
        reg = false;
    }

    if(reg)
    {
        int i = 0;

        for(const auto& it : fs.getVector()) 
        {
            string toFind = getFile(it->getFileName(), i++);

            if(matchRegex(m_Vec[2], toFind))
            {
                c.doCom(*it);
                found = true;
            }
        }
    }
    else
    {
        string toFind = getFile(m_Vec[1], 0);

        for(const auto& it : fs.getVector())
        {
            if(it->getFileName().compare(toFind) == 0)
            {
                c.doCom(*it);
                found = true;
                break;
            }
        }
    }

    if(!found)
    {
        throw CExeption(extxt.DoesntExist);
    }
}

void CCommandProcess::sendHelpCom(const CCommand& c) const
{
    c.doCom();
}

void CCommandProcess::sendWriteCom(const CCommand& c, const string& path, const string& content) const
{
    if(m_Vec.size() != 3)
    {
        sendHelpCom(CHelp());
        return;
    }
    
    c.doCom(path, content);
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
            end();
        break;

    case 10:
            current();
        break;

    case 11:
            write();
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