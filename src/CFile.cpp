#include <fstream>
#include <unistd.h>
#include <filesystem>
#include <regex>

#include "CFile.h"
#include "CFileSystem.h"

using namespace std;
using namespace std::filesystem;

ExTxt extxtf;

bool isAccessible(const string& name)
{
    return (access(name.c_str(), F_OK) == 0);
}

const string CFile::setName(const string& name) const
{
    string tmp = name;
    int num = 0;

    while(isAccessible(tmp))
    {
        tmp = name;
        tmp.append("_");
        tmp.append(to_string(++num));
    }

    return tmp;
}

void CFile::createFile() const 
{
    const string cp = setPath();

    if(isAccessible(cp))
    {
        throw CExeption(extxtf.AlreadyExists);
    }

    ofstream stream (cp, ios_base::out);

    stream.write("", 0);

    stream.close();
}

void CFile::copyFile(const string& to) const 
{
    string from = getFileName();

    if(!isAccessible(from))
    {
        throw CExeption(extxtf.IsNotAccessible);
    }

    string tmp = setName(to);

    ifstream src(from, ios_base::binary);

    ofstream dst(tmp, ios_base::binary);

    dst << src.rdbuf();

    src.close();
    dst.close();
}

void CFile::deleteFile() const 
{
    string src = getFileName();

    if(!isAccessible(src))
    {
        throw CExeption(extxtf.IsNotAccessible);
    }

    remove(src.c_str());
}

void CFile::moveFile(const string& to) const 
{
    string from = getFileName();

    if(!isAccessible(from))
    {
        throw CExeption(extxtf.IsNotAccessible);
    }

    string tmp = setName(to);

    rename(from.c_str(), tmp.c_str());
}