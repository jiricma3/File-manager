#ifndef __CLINK_H__
#define __CLINK_H__

#include <string>

#include "CFileType.h"

using namespace std;

class CLink : public CFileType
{
    public:
        CLink(const string& name) : CFileType(name, 0) {}
        virtual bool createFile();
        virtual bool copyFile(const string& to);
        virtual bool deleteFile();
        //bool changeDirectory(const string& to) override;
        bool moveFile(const string& to);
        CFileType * cloneFile() const;
};

#endif 