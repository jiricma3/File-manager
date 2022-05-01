#include <filesystem>

#include "CDir.h"

using namespace std;
using namespace std::filesystem;

bool CDir::createFile()
{
    string cp = setPath();

    if(!create_directory(cp))
    {
        return false;
    }

    return true;
}

bool CDir::copyFile(const string& to)
{
    string cp = setPath();

    if(!exists(cp))
    {
        return false;
    }

    copy(cp, to);

    return true;
}

bool CDir::copyFile(const string& from, const string& to)
{

}

bool CDir::deleteFile()
{
    string cp = setPath();

    if(!remove(cp))
    {
        return false;
    }

    return true;
}

bool CDir::deleteFile(const string& src)
{
    if(!remove(src))
    {
        return false;
    }

    return true;
}

bool CDir::moveFile(const string& to)
{
    string cp = setPath();

    if(!exists(cp))
    {
        return false;
    }

    rename(cp, to);

    return true;
}

bool CDir::moveFile(const string& from, const string& to)
{

}

CFileType * CDir::cloneFile() const
{
    return new CDir(*this);
}
