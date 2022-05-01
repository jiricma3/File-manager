#include <filesystem>

#include "CLink.h"

using namespace std;
using namespace std::filesystem;

bool CLink::createLink(const string& target)
{
    string cp = setPath();

    if(!exists(target))
    {
        return false;
    }

    create_directory_symlink(target, cp);

    return true;
}

bool CLink::copyFile(const string& to)
{
    string cp = setPath();

    if(!exists(cp))
    {
        return false;
    }

    copy_symlink(cp, to);

    return true;
}

bool CLink::copyFile(const string& from, const string& to)
{

}

bool CLink::deleteFile()
{
    string cp = setPath();

    if(!exists(cp))
    {
        return false;
    }

    remove(cp);

    return true;
}

bool CLink::deleteFile(const string& src)
{
    if(!exists(src))
    {
        return false;
    }

    remove(src);

    return true;
}

bool CLink::moveFile(const string& to)
{
    string cp = setPath();

    if(!exists(cp))
    {
        return false;
    }

    copy_symlink(cp, to);
    remove(cp);

    return true;
}

bool CLink::moveFile(const string& from, const string& to)
{

}

CFileType * CLink::cloneFile() const
{
    return new CLink(*this);
}
