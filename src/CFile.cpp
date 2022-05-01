#include <fstream>
#include <unistd.h>

#include "CFile.h"

using namespace std;

bool isAccessible(const string& name)
{
    return access(name.c_str(), F_OK) != -1;
}

bool CFile::createFile()
{
    if(isAccessible(getFileName()))
    {
        return false;
    }

    ofstream stream (getFileName(), ios_base::out);

    stream.write("", 0);

    stream.close();

    return true;
}

bool CFile::copyFile(const string& to)
{
    const char * nameC = getFileName().c_str();

    if(!isAccessible(nameC))
    {
        return false;
    }

    ifstream src(nameC, ios_base::binary);

    ofstream dst(to, ios_base::binary);

    dst << src.rdbuf();

    src.close();
    dst.close();

    return true;
}

bool CFile::copyFile(const string& from, const string& to)
{

}

bool CFile::deleteFile()
{
    const char * nameC = getFileName().c_str();

    if(!isAccessible(nameC))
    {
        return false;
    }

    remove(nameC);

    return true;
}

bool CFile::deleteFile(const string& src)
{

}

bool CFile::moveFile(const string& to)
{
    const char * nameC = getFileName().c_str();
    const char * toC = to.c_str();
    
    if(!isAccessible(nameC))
    {
        return false;
    }

    rename(nameC, toC);

    return true;
}

bool CFile::moveFile(const string& from, const string& to)
{

}

CFileType * CFile::cloneFile() const
{
    return new CFile(*this);
}