#ifndef __CFILESYSTEM_H__
#define __CFILESYSTEM_H__

#include <string>
#include <vector>
#include <memory>

#include "CFile.h"

using namespace std;

class CFileSystem
{
    public:
        CFileSystem() = default;
        ~CFileSystem() = default;
        CFileSystem(const CFileSystem& x) = delete;
        void printFileSystem(ostream& os) const;
        bool changeDirectory(const string& to);

    protected:

    private:
        vector<shared_ptr<CFile>> m_Files;
};

#endif