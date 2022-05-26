#include <filesystem>
#include <sys/stat.h>

#include "CDir.h"
#include "CFileSystem.h"

using namespace std;
using namespace std::filesystem;

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

bool CDir::createFile() const 
{
    const string cp = setPath();

    if(!create_directory(cp))
    {
        return false;
    }

    return true;
}

bool CDir::copyFile(const string& from, const string& to) const 
{
    if(!dirExists(from) || !is_directory(from))
    {
        return false;
    }

    string tmp = setName(to);

    copy(from, tmp);

    return true;
}

bool CDir::deleteFile(const string& src) const 
{
    if(!is_directory(src) || !remove(src))
    {
        return false;
    }

    return true;
}

bool CDir::moveFile(const string& from, const string& to) const 
{
    if(!dirExists(from) || !is_directory(from))
    {
        return false;
    }

    string tmp = setName(to);

    copy(from, tmp);
    remove(from);

    return true;
}
