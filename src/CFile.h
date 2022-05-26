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
        virtual const string setName(const string&) const override;
        virtual bool copyFile(const string&, const string&) const override;
        virtual bool deleteFile(const string&) const override;
        virtual bool moveFile(const string&, const string&) const override;
};

#endif