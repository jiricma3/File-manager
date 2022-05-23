#ifndef __CFILE_H__
#define __CFILE_H__

#include "CFileType.h"

using namespace std;

class CFile : public CFileType
{
    public:
        CFile() = default;
        CFile(const string& name) : CFileType(name) {}
        virtual bool createFile() const override;
        virtual bool copyFile(const string& to) const override;
        virtual bool copyFile(const string& from, const string& to) const override;
        virtual bool copyFileRegex(const string& expression, const string& to) const override;
        virtual bool deleteFile() const override;
        virtual bool deleteFile(const string& src) const override;
        virtual bool deleteFileRegex(const string& expression) const override;
        virtual bool moveFile(const string& to) const override;
        virtual bool moveFile(const string& from, const string& to) const override;
        virtual bool moveFileRegex(const string& expression, const string& to) const override;
        CFileType * cloneFile() const override;
};

#endif