#ifndef __CEXEPTION_H__
#define __CEXEPTION_H__

#include <exception>
#include <string>

using namespace std;

class CExeption : exception
{
    public:
        CExeption(const char * txt) : m_Txt(txt) {}
        ~CExeption() = default;

        const char * what () const throw () { return m_Txt; }

    private:
        const char * m_Txt; 
};

struct ExTxt
{
    const char * DoesntExist = "Source file does not exist.";
    const char * AlreadyExists = "File already exists.";
    const char * IsNotAccessible = "File is not accessible.";
    const char * CouldNotCreateLink = "Could not create symbolic link. Link might already exist or target file is not accessible.";
    const char * CouldNotChangeDir = "Could not change working directory. Path might not exist.";
    const char * CouldNotGetFsInfo = "Could not get filesystem information.";
    const char * CouldNotPrint = "Given file is a directory. Use \"list\" instead.";
    const char * CouldNotOpenFile = "Could not open file.";
};

#endif
