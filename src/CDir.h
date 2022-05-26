#ifndef __CDIR_H__
#define __CDIR_H__

#include "CFileType.h"

using namespace std;

class CDir : public CFileType
{
    public:
        CDir() = default;
        CDir(const string& name) : CFileType(name) {}
        virtual const string setName(const string&) const override;
        virtual bool createFile() const override;
        virtual bool copyFile(const string&, const string&) const override;
        virtual bool deleteFile(const string&) const override;
        virtual bool moveFile(const string&, const string&) const override;
};

#endif