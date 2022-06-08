#ifndef __CLINK_H__
#define __CLINK_H__

#include "CFileType.h"

using namespace std;

/**
 * 
 * @brief A class representing a symbolic link on a disk.
 * 
 * Performs symbolic link operations.
 * 
 */
class CLink : public CFileType
{
    public:
        CLink() = default;

        /**
         * @brief Constructing a new CLink object.
         * 
         * @param[in] name Desired link name.
         * @param[in] target The path to the file to which the link will reference to.
         */
        CLink(const string& name, const string& target) : CFileType(name), m_Target(target) {}
        virtual const string setName(const string&) const override;

        /**
         * @brief Calling the creation of a symbolic link.
         */
        virtual void createFile() const override { createLink(m_Target); }
        void createLink(const string&) const;
        virtual void copyFile(const string&) const override;
        virtual void deleteFile() const override;
        virtual void moveFile(const string&) const override;

    private:
        string m_Target; ///< The file name being referenced.
};

#endif 