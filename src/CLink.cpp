#include <filesystem>
#include <sys/stat.h>
#include <regex>

#include "CLink.h"
#include "CFileSystem.h"

using namespace std;
using namespace std::filesystem;

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

bool CLink::createLink(const string& target) const 
{
    const string cp = setPath();

    if(!fileExists(target) || linkExists(cp) || !is_regular_file(target))
    {
        return false;
    }

    create_directory_symlink(target, cp);

    return true;
}

bool CLink::copyFile(const string& from, const string& to) const 
{
    if(!linkExists(from) || !is_symlink(from))
    {
        return false;
    }

    string tmp = setName(to);

    copy_symlink(from, tmp);

    return true;
}

bool CLink::deleteFile(const string& src) const 
{
    if(!is_symlink(src) || !remove(src))
    {
        return false;
    }

    return true;
}

bool CLink::moveFile(const string& from, const string& to) const 
{
    if(!linkExists(from) || !is_symlink(from))
    {
        return false;
    }

    string tmp = setName(to);

    copy_symlink(from, tmp);
    remove(from);

    return true;
}
