#include <filesystem>
#include <sys/stat.h>

#include "CFileSystem.h"

using namespace std;
using namespace std::filesystem;

ExTxt extxtd;

bool dirExists(const string& path)
{
    struct stat info;

    return stat(path.c_str(), &info) == 0;
}

const string CDir::setName(const string& name) const
{
    string tmp = name;
    int num = 0;

    while(dirExists(tmp))
    {
        tmp = name;
        tmp.append("_");
        tmp.append(to_string(++num));
    }

    return tmp;
}

void CDir::createFile() const 
{
    const string cp = setPath();

    if(!create_directory(cp))
    {
        throw CExeption(extxtd.AlreadyExists);
    }
}

void CDir::copyFile(const string& to) const 
{
    string from = getFileName();

    if(!dirExists(from))
    {
        throw CExeption(extxtd.IsNotAccessible);
    }

    string tmp = setName(to);

    copy(from, tmp);
}

void CDir::deleteFile() const 
{
    string src = getFileName();

    if(!dirExists(src))
    {
        throw CExeption(extxtd.IsNotAccessible);
    }

    remove_all(src);
}

void CDir::moveFile(const string& to) const 
{
    string from = getFileName();

    if(!dirExists(from))
    {
        throw CExeption(extxtd.IsNotAccessible);
    }

    string tmp = setName(to);

    copy(from, tmp);
    remove_all(from);
}
