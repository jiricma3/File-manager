#ifndef __CFILETYPE_H__
#define __CFILETYPE_H__

#include <string>
#include <regex>

using namespace std;

class CFileType
{
    public:
        virtual ~CFileType() = default;
        virtual CFileType * cloneFile() const = 0;
        const string & getFileName() const;
        const string setPath() const;
        const string setPath(const string& path) const;
        virtual bool createFile() const = 0;
        virtual bool copyFile(const string& to) const = 0;
        virtual bool copyFile(const string& from, const string& to) const = 0;
        virtual bool copyFileRegex(const string& expression, const string& to) const = 0;
        virtual bool deleteFile() const = 0;
        virtual bool deleteFile(const string& src) const = 0;
        virtual bool deleteFileRegex(const string& expression) const = 0;
        virtual bool moveFile(const string& to) const = 0;
        virtual bool moveFile(const string& from, const string& to) const = 0;
        virtual bool moveFileRegex(const string& expression, const string& to) const = 0;

    protected:
        CFileType(const string& name) : m_Name(name) {};
        CFileType() = default;
        bool matchRegex(const string& expression, const string& str) const;

    private:
        string m_Name;
};

#endif