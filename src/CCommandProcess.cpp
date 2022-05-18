#include <map>

#include "CCommandProcess.h"

using namespace std;

enum code
{
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

void initCom()
{
    coms["create"] = CREATE;
    coms["copy"] = COPY;
    coms["move"] = MOVE;
    coms["delete"] = DELETE;
    coms["list"] = LIST;
    coms["media"] = MEDIA;
    coms["change"] = CHANGE;
    coms["print"] = PRINT;
    coms["help"] = HELP;
    coms["end"] = END;
}

void initOpt()
{
    opts["rf"] = RF;
    opts["rd"] = RD;
    opts["rl"] = RL;
    opts["f"] = F;
    opts["d"] = D;
    opts["l"] = L;
    opts["ll"] = LL;
    opts["h"] = H;
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

        default:
                return 8;
    }
}

void CCommandProcess::create() const
{
    int res = getOption(); 
    CCreate c = CCreate(res, m_From, m_To);

    if(res == 0 || res == 3) c.file();
    if(res == 1 || res == 4) c.dir();
    if(res == 2 || res == 5) c.link();
}

void CCommandProcess::copy() const
{
    int res = getOption();   
    CCopy c = CCopy(res, m_From, m_To);

    if(res == 0 || res == 3) c.file();
    if(res == 1 || res == 4) c.dir();
    if(res == 2 || res == 5) c.link();
}

void CCommandProcess::move() const
{
    int res = getOption();   
    CMove c = CMove(res, m_From, m_To);

    if(res == 0 || res == 3) c.file();
    if(res == 1 || res == 4) c.dir();
    if(res == 2 || res == 5) c.link();
}

void CCommandProcess::del() const
{
    int res = getOption();   
    CDelete c = CDelete(res, m_From);

    if(res == 0 || res == 3) c.file();
    if(res == 1 || res == 4) c.dir();
    if(res == 2 || res == 5) c.link();
}

void CCommandProcess::print() const
{
    CPrint c = CPrint(m_Option);
}

void CCommandProcess::list() const
{
    int res = getOption();   
    CList c = CList(res);
    c.list();
}

void CCommandProcess::change() const
{
    CChange c = CChange(m_Option);
}

void CCommandProcess::media() const
{
    CMedia();
}

void CCommandProcess::help() const
{
    CHelp();
}

void CCommandProcess::processCommand() const
{
    initCom();

    switch(coms[m_Command])
    {
        case CREATE:
                 create();
            break;

        case COPY:
                copy();
            break;
                
        case MOVE:
                move();
            break;

        case DELETE:
                del();
            break;

        case LIST:
                list();
            break;

        case MEDIA:   
                media();
            break;

        case CHANGE: 
                change();
            break;

        case PRINT:  
                print();
            break;

        case HELP:   
                help();
            break;

        case END:
                exit(EXIT_SUCCESS);
            break;
            
        default:   
                help();
            break;
    }
}