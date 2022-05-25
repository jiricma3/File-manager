#include <fstream>
#include <unistd.h>
#include <filesystem>
#include <regex>

#include "CFile.h"
#include "CFileSystem.h"

using namespace std;
using namespace std::filesystem;

bool isAccessible(const string& name)
{
    return (access(name.c_str(), F_OK) == 0);
}

bool CFile::createFile() const 
{
    const string cp = setPath();

    if(isAccessible(cp))
    {
        return false;
    }

    ofstream stream (cp, ios_base::out);

    stream.write("", 0);

    stream.close();

    return true;
}

bool CFile::copyFile(const string& to) const 
{
    const string cp = setPath();
    const string tcp = setPath(to);

    if(!isAccessible(cp) || !is_regular_file(cp))
    {
        return false;
    }

    string tmp = tcp;
    int num = 0;

    while(isAccessible(tmp))
    {
        tmp = tcp;
        tmp.append("_");
        tmp.append(to_string(++num));
    }

    ifstream src(cp, ios_base::binary);

    ofstream dst(tcp, ios_base::binary);

    dst << src.rdbuf();

    src.close();
    dst.close();

    return true;
}

bool CFile::copyFile(const string& from, const string& to) const 
{
    const string fcp = setPath(from);
    const string tcp = setPath(to);

    if(!isAccessible(fcp) || !is_regular_file(fcp))
    {
        return false;
    }

    string tmp = tcp;
    int num = 0;

    while(isAccessible(tmp))
    {
        tmp = tcp;
        tmp.append("_");
        tmp.append(to_string(++num));
    }

    ifstream src(fcp, ios_base::binary);

    ofstream dst(tmp, ios_base::binary);

    dst << src.rdbuf();

    src.close();
    dst.close();

    return true;
}

bool CFile::deleteFile() const 
{
    const string cp = setPath();

    if(!isAccessible(cp) || !is_regular_file(cp))
    {
        return false;
    }

    remove(cp.c_str());

    return true;
}

bool CFile::deleteFile(const string& src) const 
{
    const string scp = setPath(src);

    if(!isAccessible(scp) || !is_regular_file(scp))
    {
        return false;
    }

    remove(scp.c_str());

    return true;
}

bool CFile::moveFile(const string& to) const 
{
    const string cp = setPath();
    const string tcp = setPath(to);

    if(!isAccessible(cp) || !is_regular_file(cp))
    {
        return false;
    }

    string tmp = tcp;
    int num = 0;

    while(isAccessible(tmp))
    {
        tmp = tcp;
        tmp.append("_");
        tmp.append(to_string(++num));
    }

    rename(cp.c_str(), tmp.c_str());

    return true;
}

bool CFile::moveFile(const string& from, const string& to) const 
{
    const string fcp = setPath(from);
    const string tcp = setPath(to);

    if(!isAccessible(fcp) || !is_regular_file(fcp))
    {
        return false;
    }

    string tmp = tcp;
    int num = 0;

    while(isAccessible(tmp))
    {
        tmp = tcp;
        tmp.append("_");
        tmp.append(to_string(++num));
    }

    rename(fcp.c_str(), tmp.c_str());

    return true;
}

bool CFile::copyFileRegex(const string& expression, const string& to) const 
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

bool CFile::moveFileRegex(const string& expression, const string& to) const 
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

bool CFile::deleteFileRegex(const string& expression) const 
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

CFileType * CFile::cloneFile() const
{
    return new CFile(*this);
}