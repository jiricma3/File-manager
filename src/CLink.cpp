#include <filesystem>
#include <sys/stat.h>

#include "CLink.h"

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

bool CLink::createLink(const string& target)
{
    const string cp = setPath();
    const string tcp = setPath(target);

    if(!fileExists(tcp) || linkExists(cp))
    {
        return false;
    }

    create_directory_symlink(tcp, cp);

    return true;
}

bool CLink::copyFile(const string& to)
{
    const string cp = setPath();
    const string tcp = setPath(to);

    if(!linkExists(cp) || linkExists(tcp))
    {
        return false;
    }

    copy_symlink(cp, tcp);

    return true;
}

bool CLink::copyFile(const string& from, const string& to)
{
    const string fcp = setPath(from);
    const string tcp = setPath(to);

    if(!linkExists(fcp) || linkExists(tcp))
    {
        return false;
    }

    copy_symlink(fcp, tcp);

    return true;
}

bool CLink::deleteFile()
{
    const string cp = setPath();

    if(!remove(cp))
    {
        return false;
    }

    return true;
}

bool CLink::deleteFile(const string& src)
{
    const string scp = setPath(src);

    if(!remove(scp))
    {
        return false;
    }

    return true;
}

bool CLink::moveFile(const string& to)
{
    const string cp = setPath();
    const string tcp = setPath(to);

    if(!linkExists(cp) || linkExists(tcp))
    {
        return false;
    }

    copy_symlink(cp, tcp);
    remove(cp);

    return true;
}

bool CLink::moveFile(const string& from, const string& to)
{
    const string fcp = setPath(from);
    const string tcp = setPath(to);

    if(!linkExists(fcp) || linkExists(tcp))
    {
        return false;
    }

    copy_symlink(fcp, tcp);
    remove(fcp);

    return true;
}

CFileType * CLink::cloneFile() const
{
    return new CLink(*this);
}
