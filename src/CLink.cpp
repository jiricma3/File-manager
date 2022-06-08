#include <filesystem>
#include <sys/stat.h>

#include "CFileSystem.h"

using namespace std;
using namespace std::filesystem;

CExTxt extxtl; ///< Instance of the error messages class.

/**
 * @brief Determining if a symbolic link exists.
 * 
 * @param[in] path Link path.
 * 
 * @return true - link does exist.
 * @return false - link does not exist.
 */
bool linkExists(const string& path)
{
    struct stat info;

    return lstat(path.c_str(), &info) == 0;
}

/**
 * @brief Determining if a target file exists.
 * 
 * @param[in] path File path.
 * 
 * @return true - file does exist.
 * @return false - file does not exist.
 */
bool fileExists(const string& path)
{
    struct stat info;

    return stat(path.c_str(), &info) == 0;
}

/**
 * @brief Setting the correct symbolic link name.
 * 
 * If the link already exists in the destination, another name will be set.
 * 
 * See also linkExists().
 * 
 * @param[in] name Link name.
 *  
 * @return Modified link name.
 */
const string CLink::setName(const string& name) const
{
    string tmp = name;
    int num = 0;

    while(linkExists(tmp))
    {
        tmp = name;
        tmp.append("_");
        tmp.append(to_string(++num));
    }

    return tmp;
}

/**
 * @brief Creating a new symbolic link.
 * 
 * See also fileExists(), linkExists(), setPath(), CException.
 * 
 * @param[in] target The path to the file to which the link will reference to.
 * 
 * @exception CException - could not create a link.
 */
void CLink::createLink(const string& target) const 
{
    const string cp = setPath();

    if(!fileExists(target) || linkExists(cp))
    {
        throw CException(extxtl.CouldNotCreateLink);
    }

    create_symlink(target, cp);
}

/**
 * @brief Copying the symbolic link to the destination.
 * 
 * See also getFileName(), linkExists(), setName(), CException.
 * 
 * @param[in] to Destination path.
 * 
 * @exception CException - link is not accessible.
 */
void CLink::copyFile(const string& to) const 
{
    string from = getFileName();

    if(!linkExists(from))
    {
        throw CException(extxtl.IsNotAccessible);
    }

    string tmp = setName(to);

    copy_symlink(from, tmp);
}

/**
 * @brief Deleting a symbolic link.
 * 
 * See also getFileName(), linkExists(), CException.
 * 
 * @exception CException - link is not accessible.
 */
void CLink::deleteFile() const 
{
    string src = getFileName();

    if(!linkExists(src))
    {
        throw CException(extxtl.IsNotAccessible);
    }

    remove(src);
}

/**
 * @brief Moving the symbolic link to the destination.
 * 
 * See also getFileName(), linkExists(), setName(), CException.
 * 
 * @param[in] to Destination path.
 * 
 * @exception CException - link is not accessible.
 */
void CLink::moveFile(const string& to) const 
{
    string from = getFileName();

    if(!linkExists(from))
    {
        throw CException(extxtl.IsNotAccessible);
    }

    string tmp = setName(to);

    copy_symlink(from, tmp);
    remove(from);
}
