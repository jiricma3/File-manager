#ifndef __CFILESYSTEM_H__
#define __CFILESYSTEM_H__

#include <vector>
#include <memory>

#include "CFile.h"
#include "CDir.h"
#include "CLink.h"

using namespace std;

/**
 * @brief A class representing the entire file system.
 * 
 * Lists files in a directory and changes the working directory.
 * 
 */
class CFileSystem
{
    public:
        CFileSystem() = default;
        ~CFileSystem() = default;
        CFileSystem(const CFileSystem&) = delete;
        void printFileSystem() const;
        void printFileSystemLong() const;
        bool changeDirectory(const string&) const;
        vector<shared_ptr<CFileType>> & getVector();
        void loadFiles() const;
        void loadFiles(const string&) const;

    private:
        void loadVector(const string&) const;
        static vector<shared_ptr<CFileType>> m_Vec; ///< Vector containing pointers to files in the directory.
};

/**
 * @brief Class containing the format of the output text.
 * 
 */
class CProperties
{
    public:
        string dirColor = "\033[38;2;0;140;212m"; ///< Directory text color in the listing.
        string fileColor = "\033[38;2;255;255;255m"; ///< Regular file text color in the listing.
        string linkColor = "\033[38;2;210;0;200m"; ///< Symbolic link text color in the listing.
        string resetColor = "\033[0m"; ///< Text format reset.
};

#endif