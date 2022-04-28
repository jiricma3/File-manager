#ifndef __CFILE_H__
#define __CFILE_H__

#include <string>

#include "CFileType.h"

using namespace std;

class CFile : public CFileType
{
    public:
        CFile(const string& name) : CFileType(name, 0) { createFile(); }
        CFile(const CFile& x) = delete;
        virtual bool createFile();
        virtual bool copyFile(const string& to);
        virtual bool deleteFile();
        virtual bool moveFile(const string& to);
        CFileType * cloneFile() const;
};

#endif