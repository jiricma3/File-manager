#ifndef __CDIR_H__
#define __CDIR_H__

#include <string>

#include "CFileType.h"

using namespace std;

class CDir : public CFileType
{
    public:
        CDir(const string& name) : CFileType(name, 4096) {}
        virtual bool createFile();
        virtual bool copyFile(const string& to);
        virtual bool deleteFile();
        //bool changeDirectory(const string& to) override;
        virtual bool moveFile(const string& to);
        CFileType * cloneFile() const;
};

#endif