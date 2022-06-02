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
        virtual void createFile() const override;
        virtual void copyFile(const string&) const override;
        virtual void deleteFile() const override;
        virtual void moveFile(const string&) const override;
};

#endif