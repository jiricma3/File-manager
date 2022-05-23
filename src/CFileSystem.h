#ifndef __CFILESYSTEM_H__
#define __CFILESYSTEM_H__

#include <string>
#include <vector>
#include <memory>

#include "CFileType.h"
#include "CFile.h"
#include "CDir.h"
#include "CLink.h"

using namespace std;

class CFileSystem
{
    public:
        CFileSystem() = default;
        ~CFileSystem() = default;
        CFileSystem(const CFileSystem& x) = delete;
        void printFileSystem() const;
        void printFileSystemLong() const;
        bool changeDirectory(const string& to) const;
        vector<shared_ptr<CFileType>> & getVector();
        void loadFiles() const;

    private:
        static vector<shared_ptr<CFileType>> m_Vec;
};

#endif