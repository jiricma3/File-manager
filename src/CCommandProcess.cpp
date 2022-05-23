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

    switch(opts[m_Option])
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
    CCreate c = CCreate();
    sendFileCom(c, getOption());
}

void CCommandProcess::copy() const
{
    
}

void CCommandProcess::move() const
{
    
}

void CCommandProcess::del() const
{
    
}

void CCommandProcess::print() const
{
    
}

void CCommandProcess::list() const
{
    
}

void CCommandProcess::change() const
{
    
}

void CCommandProcess::media() const
{
    
}

void CCommandProcess::help() const
{
    
}

void CCommandProcess::sendFileCom(const CCommand& c, int res) const
{
    if(res == 0 || res == 3) c.doCom(CFile(), m_From, m_To);
    if(res == 1 || res == 4) c.doCom(CDir(), m_From, m_To);
    if(res == 2 || res == 5) c.doCom(CLink(), m_From, m_To);
    //if(res == 7) c.help();
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

    for(const auto& it : vec)
    {
        if(it.compare(m_Vec[0]) == 0)
        {
            
        }

        i++;
    }
}