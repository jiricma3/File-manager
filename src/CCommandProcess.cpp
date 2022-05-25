#include <map>

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
            
        case LL:
                return 6;

        case H:
                return 7;
        
        case UN:
                return 7;

        default:
                return 7;
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
    sendFileCom(CDelete(), getOption());
}

void CCommandProcess::print() const
{
    sendFsCom(CPrint(), m_Vec[1]);
}

void CCommandProcess::list() const
{
    sendListCom(CList(), getOption() == 5 ? true : false);
}

void CCommandProcess::change() const
{
    sendFsCom(CChange(), m_Vec[1]);
}

void CCommandProcess::media() const
{
    sendCom(CMedia());
}

void CCommandProcess::help() const
{
    sendCom(CHelp());
}

void CCommandProcess::sendCreateCom(const CCommand& c, int res) const
{
    if(res == 0 || res == 3) c.doCom(CFile(m_Vec[2]));
    if(res == 1 || res == 4) c.doCom(CDir(m_Vec[2]));
    if(res == 2 || res == 5) m_Vec.size() == 4 ? c.doCom(CLink(m_Vec[2], m_Vec[3])) : sendCom(CHelp());
}

void CCommandProcess::sendFileCom(const CCommand& c, int res) const
{
    CFileSystem fs;
    // shared_ptr<CFileType> file;

    if(res < 6)
    {
        for(const auto& it : fs.getVector())
        {
            if(it->getFileName().compare(m_Vec[1]) == 0)
            {
                c.doCom(*it, m_Vec[2]);
                break;
            }
        }
    }
}

void CCommandProcess::sendListCom(const CCommand& c, bool l) const
{
    c.doCom(l);
}

void CCommandProcess::sendCom(const CCommand& c) const
{
    c.doCom();
}

void CCommandProcess::sendFsCom(const CCommand& c, const string& src) const
{
    c.doCom(src);
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
            break;
        }

        i++;
    }
}