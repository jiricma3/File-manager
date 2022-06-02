#include <filesystem>
#include <sys/stat.h>
#include <regex>

#include "CLink.h"
#include "CFileSystem.h"

using namespace std;
using namespace std::filesystem;

ExTxt extxtl;

bool linkExists(const string& path)
{
    struct stat info;

    return lstat(path.c_str(), &info) == 0;
}

bool fileExists(const string& path)
{
    struct stat info;

    return stat(path.c_str(), &info) == 0;
}

const string CLink::setName(const string& name) const
{
    string tmp = name;
    int num = 0;

    while(linkExists(tmp))
    {
        tmp = name;
        tmp.append("_");
        tmp.append(to_string(++num));
    }

    return tmp;
}

void CLink::createLink(const string& target) const 
{
    const string cp = setPath();

    if(!fileExists(target) || linkExists(cp))
    {
        throw CExeption(extxtl.CouldNotCreateLink);
    }

    create_symlink(target, cp);
}

void CLink::copyFile(const string& to) const 
{
    string from = getFileName();

    if(!linkExists(from))
    {
        throw CExeption(extxtl.IsNotAccessible);
    }

    string tmp = setName(to);

    copy_symlink(from, tmp);
}

void CLink::deleteFile() const 
{
    string src = getFileName();

    if(!remove(src))
    {
        throw CExeption(extxtl.IsNotAccessible);
    }
}

void CLink::moveFile(const string& to) const 
{
    string from = getFileName();

    if(!linkExists(from))
    {
        throw CExeption(extxtl.IsNotAccessible);
    }

    string tmp = setName(to);

    copy_symlink(from, tmp);
    remove(from);
}
