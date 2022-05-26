#ifndef __CFILETYPE_H__
#define __CFILETYPE_H__

#include <string>
#include <regex>

using namespace std;

class CFileType
{
    public:
        virtual ~CFileType() = default;
        const string & getFileName() const;
        const string setPath() const;
        virtual const string setName(const string&) const = 0;
        virtual bool createFile() const = 0;
        virtual bool copyFile(const string&, const string&) const = 0;
        virtual bool deleteFile(const string&) const = 0;
        virtual bool moveFile(const string&, const string&) const = 0;

    protected:
        CFileType(const string& name) : m_Name(name) {};
        CFileType() = default;

    private:
        string m_Name;
};

#endif