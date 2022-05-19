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
        vector<string> & getVector();
        void loadFiles() const;

    private:
        static vector<string> m_Files;
};

#endif