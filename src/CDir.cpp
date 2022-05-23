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

bool CDir::createFile() const 
{
    const string cp = setPath();

    if(!create_directory(cp))
    {
        return false;
    }

    return true;
}

bool CDir::copyFile(const string& to) const 
{
    const string cp = setPath();
    const string tcp = setPath(to);

    if(!dirExists(cp) || !is_directory(cp))
    {
        return false;
    }

    string tmp = tcp;
    int num = 0;

    while(dirExists(tmp))
    {
        tmp = tcp;
        tmp.append("_");
        tmp.append(to_string(++num));
    }

    copy(cp, tmp);

    return true;
}

bool CDir::copyFile(const string& from, const string& to) const 
{
    const string fcp = setPath(from);
    const string tcp = setPath(to);

    if(!dirExists(fcp) || !is_directory(fcp))
    {
        return false;
    }

    string tmp = tcp;
    int num = 0;

    while(dirExists(tmp))
    {
        tmp = tcp;
        tmp.append("_");
        tmp.append(to_string(++num));
    }

    copy(fcp, tmp);

    return true;
}

bool CDir::deleteFile() const 
{
    const string cp = setPath();

    if(!is_directory(cp) || !remove(cp))
    {
        return false;
    }

    return true;
}

bool CDir::deleteFile(const string& src) const 
{
    const string scp = setPath(src);

    if(!is_directory(scp) || !remove(scp))
    {
        return false;
    }

    return true;
}

bool CDir::moveFile(const string& to) const 
{
    const string cp = setPath();
    const string tcp = setPath(to);


    if(!dirExists(cp) || !is_directory(cp))
    {
        return false;
    }

    string tmp = tcp;
    int num = 0;

    while(dirExists(tmp))
    {
        tmp = tcp;
        tmp.append("_");
        tmp.append(to_string(++num));
    }

    copy(cp, tmp);
    remove(cp);

    return true;
}

bool CDir::moveFile(const string& from, const string& to) const 
{
    const string fcp = setPath(from);
    const string tcp = setPath(to);

    if(!dirExists(fcp) || !is_directory(fcp))
    {
        return false;
    }

    string tmp = tcp;
    int num = 0;

    while(dirExists(tmp))
    {
        tmp = tcp;
        tmp.append("_");
        tmp.append(to_string(++num));
    }

    copy(fcp, tmp);
    remove(fcp);

    return true;
}

bool CDir::copyFileRegex(const string& expression, const string& to) const 
{
    CFileSystem fs;
    fs.loadFiles();
    vector<shared_ptr<CFileType>> vec = fs.getVector();
    
    for(const auto& it : vec)
    {
        if(matchRegex(expression, it->getFileName()))
        {
            copyFile(it->getFileName(), to);
        }
    }

    return true;
}

bool CDir::moveFileRegex(const string& expression, const string& to) const 
{
    CFileSystem fs;
    fs.loadFiles();
    vector<shared_ptr<CFileType>> vec = fs.getVector();

    for(const auto& it : vec) 
    {
        if(matchRegex(expression, it->getFileName()))
        {
            moveFile(it->getFileName(), to);
        }
    }

    return true;
}

bool CDir::deleteFileRegex(const string& expression) const
{
    CFileSystem fs;
    fs.loadFiles();
    vector<shared_ptr<CFileType>> vec = fs.getVector();

    for(const auto& it : vec) 
    {
        if(matchRegex(expression, it->getFileName()))
        {
            deleteFile(it->getFileName());
        }
    }

    return true;
}

CFileType * CDir::cloneFile() const
{
    return new CDir(*this);
}
