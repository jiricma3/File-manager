#include "CParser.h"
#include "CCommandProcess.h"

using namespace std;

void CParser::one()
{
    CCommandProcess c = CCommandProcess(0, m_Vec[0]);
}

void CParser::two()
{
    CCommandProcess c = CCommandProcess(0, m_Vec[0], m_Vec[1]);
}

void CParser::three()
{
    CCommandProcess c = CCommandProcess(1, m_Vec[0], m_Vec[1], m_Vec[2]);
}

void CParser::four()
{
    if(m_Vec[1] == "-l")
    {
        CCommandProcess c = CCommandProcess("l", m_Vec[0], m_Vec[1], m_Vec[2], m_Vec[3]);
    }
    else
    {
        CCommandProcess c = CCommandProcess(2, m_Vec[0], m_Vec[1], m_Vec[2], m_Vec[3]);
    }
}

void CParser::help()
{
    CCommandProcess c = CCommandProcess(0, "help");
}

bool CParser::parseCommands()
{
    // switch(m_Vec.size())
    // {
    //     case 1:
    //             one();
    //         break;

    //     case 2:
    //             two();
    //         break;

    //     case 3:
    //             three();
    //         break;

    //     case 4:
    //             four();
    //         break;

    //     default:
    //             help();
    //         break;
    // }

    CCommandProcess c = CCommandProcess(m_Vec);

    return true;
}