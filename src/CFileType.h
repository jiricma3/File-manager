#ifndef __CFILETYPE_H__
#define __CFILETYPE_H__

#include <string>

using namespace std;

class CFileType
{
    public:
        virtual ~CFileType() = default;
        virtual CFileType * cloneFile() const = 0;
        string & getFileName();
        string setPath();

    protected:
        CFileType(const string& name) : m_Name(name) {};

    private:
        virtual bool createFile() = 0;
        virtual bool copyFile(const string& to) = 0;
        virtual bool copyFile(const string& from, const string& to) = 0;
        virtual bool deleteFile() = 0;
        virtual bool deleteFile(const string& src) = 0;
        virtual bool moveFile(const string& to) = 0;
        virtual bool moveFile(const string& from, const string& to) = 0;

        string m_Name;
};

#endif