#ifndef __CFILETYPE_H__
#define __CFILETYPE_H__

#include <regex>

#include "CException.h"

using namespace std;

/**
 * @brief An abstract class representing all the files on a disk.
 * 
 * All derived file classes inherit methods from this class.
 * 
 */
class CFileType
{
    public:
        virtual ~CFileType() = default;
        const string & getFileName() const;
        const string setPath() const;
        virtual const string setName(const string&) const = 0;
        virtual void createFile() const = 0;
        virtual void copyFile(const string&) const = 0;
        virtual void deleteFile() const = 0;
        virtual void moveFile(const string&) const = 0;

    protected:

        /**
         * @brief Constructing a new CFileType object.
         * 
         * @param[in] name File name.
         */
        CFileType(const string& name) : m_Name(name) {};

    private:
        string m_Name; ///< File name.
};

#endif