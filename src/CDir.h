#ifndef __CDIR_H__
#define __CDIR_H__

#include "CFileType.h"

using namespace std;

class CDir : public CFileType
{
    public:
        CDir(const string& name) : CFileType(name) { createFile(); }
        virtual bool createFile() override;
        virtual bool copyFile(const string& to) override;
        virtual bool copyFile(const string& from, const string& to) override;
        virtual bool copyFileRegex(const string& expression, const string& to) override;
        virtual bool deleteFile() override;
        virtual bool deleteFile(const string& src) override;
        virtual bool deleteFileRegex(const string& expression, const string& from) override;
        virtual bool moveFile(const string& to) override;
        virtual bool moveFile(const string& from, const string& to) override;
        virtual bool moveFileRegex(const string& expression, const string& to) override;
        CFileType * cloneFile() const override;
};

#endif