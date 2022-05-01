#ifndef __CFILE_H__
#define __CFILE_H__

#include <string>

#include "CFileType.h"

using namespace std;

class CFile : public CFileType
{
    public:
        CFile(const string& name) : CFileType(name) { createFile(); }
        virtual bool createFile() override;
        virtual bool copyFile(const string& to) override;
        virtual bool copyFile(const string& from, const string& to) override;
        virtual bool deleteFile() override;
        virtual bool deleteFile(const string& src) override;
        virtual bool moveFile(const string& to) override;
        virtual bool moveFile(const string& from, const string& to) override;
        CFileType * cloneFile() const override;
};

#endif