#include <fstream>
#include <unistd.h>
#include <filesystem>
#include <regex>

#include "CFile.h"
#include "CFileSystem.h"

using namespace std;
using namespace std::filesystem;

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

bool CFile::createFile() const 
{
    const string cp = setPath();

    if(isAccessible(cp))
    {
        return false;
    }

    ofstream stream (cp, ios_base::out);

    stream.write("", 0);

    stream.close();

    return true;
}

bool CFile::copyFile(const string& from, const string& to) const 
{
    if(!isAccessible(from) || !is_regular_file(from))
    {
        return false;
    }

    string tmp = setName(to);

    ifstream src(from, ios_base::binary);

    ofstream dst(tmp, ios_base::binary);

    dst << src.rdbuf();

    src.close();
    dst.close();

    return true;
}

bool CFile::deleteFile(const string& src) const 
{
    if(!isAccessible(src) || !is_regular_file(src))
    {
        return false;
    }

    remove(src.c_str());

    return true;
}

bool CFile::moveFile(const string& from, const string& to) const 
{
    if(!isAccessible(from) || !is_regular_file(from))
    {
        return false;
    }

    string tmp = setName(to);

    rename(from.c_str(), tmp.c_str());

    return true;
}