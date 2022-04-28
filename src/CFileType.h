#ifndef __CFILETYPE_H__
#define __CFILETYPE_H__

#include <string>

using namespace std;

class CFileType
{
    public:
        virtual ~CFileType() = default;
        virtual CFileType * cloneFile() const = 0;
        size_t getFileSize() const;
        string & getFileName();

    protected:
        CFileType(const string& name, size_t size) : m_Name(name), m_Size(size) {};

    private:
        virtual bool createFile() = 0;
        virtual bool copyFile(const string& to) = 0;
        virtual bool deleteFile() = 0;
        virtual bool moveFile(const string& to) = 0;

        string m_Name;
        size_t m_Size;
};

#endif