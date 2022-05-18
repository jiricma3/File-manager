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

bool CLink::createLink(const string& target) const 
{
    const string cp = setPath();
    const string tcp = setPath(target);

    if(!fileExists(tcp) || linkExists(cp) || !is_regular_file(tcp))
    {
        return false;
    }

    create_directory_symlink(tcp, cp);

    return true;
}

bool CLink::copyFile(const string& to) const 
{
    const string cp = setPath();
    const string tcp = setPath(to);

    if(!linkExists(cp) || !is_symlink(cp))
    {
        return false;
    }

    string tmp = tcp;
    int num = 0;

    while(linkExists(tmp))
    {
        tmp = tcp;
        tmp.append("_");
        tmp.append(to_string(++num));
    }

    copy_symlink(cp, tmp);

    return true;
}

bool CLink::copyFile(const string& from, const string& to) const 
{
    const string fcp = setPath(from);
    const string tcp = setPath(to);

    if(!linkExists(fcp) || !is_symlink(fcp))
    {
        return false;
    }

    string tmp = tcp;
    int num = 0;

    while(linkExists(tmp))
    {
        tmp = tcp;
        tmp.append("_");
        tmp.append(to_string(++num));
    }

    copy_symlink(fcp, tmp);

    return true;
}

bool CLink::deleteFile() const 
{
    const string cp = setPath();

    if(!is_symlink(cp) || !remove(cp))
    {
        return false;
    }

    return true;
}

bool CLink::deleteFile(const string& src) const 
{
    const string scp = setPath(src);

    if(!is_symlink(scp) || !remove(scp))
    {
        return false;
    }

    return true;
}

bool CLink::moveFile(const string& to) const 
{
    const string cp = setPath();
    const string tcp = setPath(to);

    if(!linkExists(cp) || !is_symlink(cp))
    {
        return false;
    }

    string tmp = tcp;
    int num = 0;

    while(linkExists(tmp))
    {
        tmp = tcp;
        tmp.append("_");
        tmp.append(to_string(++num));
    }

    copy_symlink(cp, tmp);
    remove(cp);

    return true;
}

bool CLink::moveFile(const string& from, const string& to) const 
{
    const string fcp = setPath(from);
    const string tcp = setPath(to);

    if(!linkExists(fcp) || !is_symlink(fcp))
    {
        return false;
    }

    string tmp = tcp;
    int num = 0;

    while(linkExists(tmp))
    {
        tmp = tcp;
        tmp.append("_");
        tmp.append(to_string(++num));
    }

    copy_symlink(fcp, tmp);
    remove(fcp);

    return true;
}

bool CLink::copyFileRegex(const string& expression, const string& to) const 
{
    CFileSystem fs;
    fs.loadFiles();
    vector<string> vec = fs.getVector();

    for(const auto& it : vec) 
    {
        if(matchRegex(expression, it))
        {
            copyFile(it, to);
        }
    }

    return true;
}

bool CLink::moveFileRegex(const string& expression, const string& to) const 
{
    CFileSystem fs;
    fs.loadFiles();
    vector<string> vec = fs.getVector();

    for(const auto& it : vec) 
    {
        if(matchRegex(expression, it))
        {
            moveFile(it, to);
        }
    }

    return true;
}

bool CLink::deleteFileRegex(const string& expression) const 
{
    CFileSystem fs;
    fs.loadFiles();
    vector<string> vec = fs.getVector();

    for(const auto& it : vec) 
    {
        if(matchRegex(expression, it))
        {
            deleteFile(it);
        }
    }

    return true;
}

CFileType * CLink::cloneFile() const
{
    return new CLink(*this);
}
