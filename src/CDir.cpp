#include <filesystem>
#include <sys/stat.h>

#include "CFileSystem.h"

using namespace std;
using namespace std::filesystem;

CExTxt extxtd; ///< Instance of the error messages class.

/**
 * @brief Determining if a directory exists.
 * 
 * @param[in] path Directory path.
 * 
 * @return true - directory does exist.
 * @return false - directory does not exist.
 */
bool dirExists(const string& path)
{
    struct stat info;

    return stat(path.c_str(), &info) == 0;
}

/**
 * @brief Setting the correct directory name.
 * 
 * If the directory already exists in the destination, another name will be set.
 * 
 * See also dirExists().
 * 
 * @param[in] name Directory name.
 *  
 * @return Modified directory name.
 */
const string CDir::setName(const string& name) const
{
    string tmp = name;
    int num = 0;

    while(dirExists(tmp))
    {
        tmp = name;
        tmp.append("_");
        tmp.append(to_string(++num));
    }

    return tmp;
}

/**
 * @brief Creating a new directory.
 * 
 * See also dirExists(), setPath(), CException.
 * 
 * @exception CException - directory already exists.
 */
void CDir::createFile() const 
{
    const string cp = setPath();

    if(dirExists(cp))
    {
        throw CException(extxtd.AlreadyExists);
    }

    create_directory(cp);
}

/**
 * @brief Copying the directory to the destination.
 * 
 * See also getFileName(), dirExists(), setName(), CException.
 * 
 * @param[in] to Destination path.
 * 
 * @exception CException - directory is not accessible.
 */
void CDir::copyFile(const string& to) const 
{
    string from = getFileName();

    if(!dirExists(from))
    {
        throw CException(extxtd.IsNotAccessible);
    }

    string tmp = setName(to);

    copy(from, tmp);
}

/**
 * @brief Deleting a directory.
 * 
 * See also getFileName(), dirExists(), CException.
 * 
 * @exception CException - directory is not accessible.
 */
void CDir::deleteFile() const 
{
    string src = getFileName();

    if(!dirExists(src))
    {
        throw CException(extxtd.IsNotAccessible);
    }

    remove_all(src);
}

/**
 * @brief Moving the directory to the destination.
 * 
 * See also getFileName(), dirExists(), setName(), CException.
 * 
 * @param[in] to Destination path.
 * 
 * @exception CException - directory is not accessible.
 */
void CDir::moveFile(const string& to) const 
{
    string from = getFileName();

    if(!dirExists(from))
    {
        throw CException(extxtd.IsNotAccessible);
    }

    string tmp = setName(to);

    copy(from, tmp);
    remove_all(from);
}
