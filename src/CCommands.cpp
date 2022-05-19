#include <iostream>
#include <fstream>
#include <filesystem>

#include "CCommands.h"

using namespace std;
using namespace std::filesystem;

void CCreate::file() const
{
    CFile f = CFile(m_Name);
}

void CCreate::dir() const
{
    CDir d = CDir(m_Name);
}

void CCreate::link() const
{
    CLink l = CLink(m_Name, m_Target);
}

void CCopy::file() const
{
    if(getOpt() == 0)
    {
        CFile f;
        f.copyFileRegex(m_From, m_To);
    }

    if(getOpt() == 3)
    {
        CFile f;
        f.copyFile(m_From, m_To);
    }
}

void CCopy::dir() const
{
    if(getOpt() == 1)
    {
        CDir d;
        d.copyFileRegex(m_From, m_To);
    }

    if(getOpt() == 4)
    {
        CDir d;
        d.copyFile(m_From, m_To);
    }
}

void CCopy::link() const
{
    if(getOpt() == 2)
    {
        CLink l;
        l.copyFileRegex(m_From, m_To);
    }

    if(getOpt() == 5)
    {
        CLink l;
        l.copyFile(m_From, m_To);
    }
}

void CMove::file() const
{
    if(getOpt() == 0)
    {
        CFile f;
        f.moveFileRegex(m_From, m_To);
    }

    if(getOpt() == 3)
    {
        CFile f;
        f.moveFile(m_From, m_To);
    }
}

void CMove::dir() const
{
    if(getOpt() == 1)
    {
        CDir d;
        d.moveFileRegex(m_From, m_To);
    }

    if(getOpt() == 4)
    {
        CDir d;
        d.moveFile(m_From, m_To);
    }
}

void CMove::link() const
{
    if(getOpt() == 2)
    {
        CLink l;
        l.moveFileRegex(m_From, m_To);
    }

    if(getOpt() == 5)
    {
        CLink l;
        l.moveFile(m_From, m_To);
    }
}

void CDelete::file() const
{
    if(getOpt() == 0)
    {
        CFile f;
        f.deleteFileRegex(m_From);
    }

    if(getOpt() == 3)
    {
        CFile f;
        f.deleteFile(m_From);
    }
}

void CDelete::dir() const
{
    if(getOpt() == 1)
    {
        CDir d;
        d.deleteFileRegex(m_From);
    }

    if(getOpt() == 4)
    {
        CDir d;
        d.deleteFile(m_From);
    }
}

void CDelete::link() const
{
    if(getOpt() == 2)
    {
        CLink l;
        l.deleteFileRegex(m_From);
    }

    if(getOpt() == 5)
    {
        CLink l;
        l.deleteFile(m_From);
    }
}

void CPrint::print() const
{
    if(!is_regular_file(m_Name))
    {
        return;
    }

    ifstream f(m_Name);

    if(f.is_open())
    {
        cout << f.rdbuf();
    }
}

void CList::list() const
{
    CFileSystem fs;

    if(m_Opt == 6)
    {
        fs.printFileSystemLong();
    }
    else
    {
        fs.printFileSystem();
    }
}

void CChange::change() const
{
    CFileSystem fs;
    fs.changeDirectory(m_To);
}

void CHelp::help() const
{
    cout << "help todo" << endl;
}

void CMedia::media() const
{
    //space_info si = space(current_path());
    cout << "media todo" << endl;
}

void CCreate::help() const
{
    cout << "create help todo" << endl;
}

void CCopy::help() const
{
    cout << "copy help todo" << endl;
}

void CMove::help() const
{
    cout << "move help todo" << endl;
}

void CDelete::help() const
{
    cout << "delete help todo" << endl;
}

void CPrint::help() const
{
    cout << "print help todo" << endl;
}

void CList::help() const
{
    cout << "list help todo" << endl;
}

void CChange::help() const
{
    cout << "change help todo" << endl;
}

void CMedia::help() const
{
    cout << "media help todo" << endl;
}