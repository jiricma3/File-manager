#include <filesystem>
#include <sys/stat.h>

#include "CDir.h"

using namespace std;
using namespace std::filesystem;

bool dirExists(const string& path)
{
    struct stat info;

    return stat(path.c_str(), &info) == 0;
}

bool CDir::createFile()
{
    const string cp = setPath();

    if(!create_directory(cp))
    {
        return false;
    }

    return true;
}

bool CDir::copyFile(const string& to)
{
    const string cp = setPath();
    const string tcp = setPath(to);

    if(!dirExists(cp) || dirExists(tcp))
    {
        return false;
    }

    copy(cp, tcp);

    return true;
}

bool CDir::copyFile(const string& from, const string& to)
{
    const string fcp = setPath(from);
    const string tcp = setPath(to);

    if(!dirExists(fcp) || dirExists(tcp))
    {
        return false;
    }

    copy(fcp, tcp);

    return true;
}

bool CDir::deleteFile()
{
    const string cp = setPath();

    if(!remove(cp))
    {
        return false;
    }

    return true;
}

bool CDir::deleteFile(const string& src)
{
    const string scp = setPath(src);

    if(!remove(scp))
    {
        return false;
    }

    return true;
}

bool CDir::moveFile(const string& to)
{
    const string cp = setPath();
    const string tcp = setPath(to);


    if(!dirExists(cp) || dirExists(tcp))
    {
        return false;
    }

    rename(cp, tcp);

    return true;
}

bool CDir::moveFile(const string& from, const string& to)
{
    const string fcp = setPath(from);
    const string tcp = setPath(to);

    if(!dirExists(fcp) || dirExists(tcp))
    {
        return false;
    }

    rename(fcp, tcp);

    return true;
}

bool CDir::copyFileRegex(const string& expression, const string& to)
{

}

bool CDir::moveFileRegex(const string& expression, const string& from)
{

}

bool CDir::deleteFileRegex(const string& expression, const string& to)
{

}

CFileType * CDir::cloneFile() const
{
    return new CDir(*this);
}
