#include <fstream>
#include <unistd.h>
#include <filesystem>

#include "CFile.h"

using namespace std;

bool isAccessible(const string& name)
{
    fstream fs;
    fs.open(name, ios_base::in);
    return fs.is_open() ? true : false;
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

CFileType * CFile::cloneFile() const
{

}