#include <fstream>
#include <unistd.h>

#include "CFile.h"

using namespace std;

bool isAccessible(const string& name)
{
    return access(name.c_str(), F_OK) == 0;
}

bool CFile::createFile()
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

bool CFile::copyFile(const string& to)
{
    const string cp = setPath();
    const string tcp = setPath(to);

    if(!isAccessible(cp) || isAccessible(tcp))
    {
        return false;
    }

    ifstream src(cp, ios_base::binary);

    ofstream dst(tcp, ios_base::binary);

    dst << src.rdbuf();

    src.close();
    dst.close();

    return true;
}

bool CFile::copyFile(const string& from, const string& to)
{
    const string fcp = setPath(from);
    const string tcp = setPath(to);

    if(!isAccessible(fcp) || isAccessible(tcp))
    {
        return false;
    }

    ifstream src(fcp, ios_base::binary);

    ofstream dst(tcp, ios_base::binary);

    dst << src.rdbuf();

    src.close();
    dst.close();

    return true;
}

bool CFile::deleteFile()
{
    const string cp = setPath();

    if(!isAccessible(cp))
    {
        return false;
    }

    remove(cp.c_str());

    return true;
}

bool CFile::deleteFile(const string& src)
{
    const string scp = setPath(src);

    if(!isAccessible(scp))
    {
        return false;
    }

    remove(scp.c_str());

    return true;
}

bool CFile::moveFile(const string& to)
{
    const string cp = setPath();
    const string tcp = setPath(to);

    if(!isAccessible(cp) || isAccessible(tcp))
    {
        return false;
    }

    rename(cp.c_str(), tcp.c_str());

    return true;
}

bool CFile::moveFile(const string& from, const string& to)
{
    const string fcp = setPath(from);
    const string tcp = setPath(to);

    if(!isAccessible(fcp) || isAccessible(tcp))
    {
        return false;
    }

    rename(fcp.c_str(), tcp.c_str());

    return true;
}

CFileType * CFile::cloneFile() const
{
    return new CFile(*this);
}