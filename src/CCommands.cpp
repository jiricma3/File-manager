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

void CDelete::doCom(const CFileType& x, const string& from, const string& to) const
{
    x.deleteFile(from);
}