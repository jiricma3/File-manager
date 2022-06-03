#ifndef __CFILETYPE_H__
#define __CFILETYPE_H__

#include <regex>

#include "CExeption.h"

using namespace std;

class CFileType
{
    public:
        virtual ~CFileType() = default;
        const string & getFileName() const;
        const string setPath() const;
        virtual const string setName(const string&) const = 0;
        virtual void createFile() const = 0;
        virtual void copyFile(const string&) const = 0;
        virtual void deleteFile() const = 0;
        virtual void moveFile(const string&) const = 0;

    protected:
        CFileType(const string& name) : m_Name(name) {};

    private:
        string m_Name;
};

#endif