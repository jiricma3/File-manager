#include <iostream>
#include <fstream>
#include <filesystem>

#include "CCommands.h"

using namespace std;
using namespace std::filesystem;

void CCreate::doCom(const CFileType& x) const
{
    x.createFile();
}

void CCopy::doCom(const CFileType& x, const string& from, const string& to) const
{
    x.copyFile(from, to);
}

void CMove::doCom(const CFileType& x, const string& from, const string& to) const
{
    x.moveFile(from, to);
}

void CDelete::doCom(const CFileType& x, const string& from) const
{
    x.deleteFile(from);
}

void CList::doCom(bool l) const
{
    CFileSystem fs;

    if(!l)
    {
        fs.printFileSystem();
    }
    else
    {
        fs.printFileSystemLong();
    }
}

void CPrint::doCom(const string& src) const
{
    ifstream f(src);

    if(f.is_open())
    {
        cout << f.rdbuf();
    }
}

void CMedia::doCom() const
{
    cout << "media todo" << endl;
}

void CChange::doCom(const string& to) const
{
    CFileSystem fs;
    fs.changeDirectory(to);
}

void CHelp::doCom() const
{
    cout << "help todo" << endl;
}