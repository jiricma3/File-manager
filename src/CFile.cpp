#include <fstream>
#include <unistd.h>
#include <filesystem>

#include "CFileSystem.h"

using namespace std;
using namespace std::filesystem;

CExTxt extxtf; ///< Instance of the error messages class.

/**
 * @brief Determining if a file exists.
 * 
 * @param[in] name File path.
 * 
 * @return true - file does exist.
 * @return false - file does not exist.
 */
bool isAccessible(const string& name)
{
    return (access(name.c_str(), F_OK) == 0);
}

/**
 * @brief Setting the correct file name.
 * 
 * If the file already exists in the destination, another name will be set.
 * 
 * See also isAccessible().
 * 
 * @param[in] name File name.
 *  
 * @return Modified file name.
 */
const string CFile::setName(const string& name) const
{
    string tmp = name;
    int num = 0;

    while(isAccessible(tmp))
    {
        tmp = name;
        tmp.append("_");
        tmp.append(to_string(++num));
    }

    return tmp;
}

/**
 * @brief Creating a new regular file.
 * 
 * See also isAccessible(), setPath(), CException.
 * 
 * @exception CException - file already exists.
 */
void CFile::createFile() const 
{
    const string cp = setPath();

    if(isAccessible(cp))
    {
        throw CException(extxtf.AlreadyExists);
    }

    ofstream stream (cp, ios_base::out);

    stream.write("", 0);

    stream.close();
}

/**
 * @brief Copying the regular file to the destination.
 * 
 * See also getFileName(), isAccessible(), setName(), CException.
 * 
 * @param[in] to Destination path.
 * 
 * @exception CException - file is not accessible.
 */
void CFile::copyFile(const string& to) const 
{
    string from = getFileName();

    if(!isAccessible(from))
    {
        throw CException(extxtf.IsNotAccessible);
    }

    string tmp = setName(to);

    ifstream src(from, ios_base::binary);

    ofstream dst(tmp, ios_base::binary);

    dst << src.rdbuf();

    src.close();
    dst.close();
}

/**
 * @brief Deleting a regular file.
 * 
 * See also getFileName(), isAccessible(), CException.
 * 
 * @exception CException - file is not accessible.
 */
void CFile::deleteFile() const 
{
    string src = getFileName();

    if(!isAccessible(src))
    {
        throw CException(extxtf.IsNotAccessible);
    }

    remove(src.c_str());
}

/**
 * @brief Moving the regular file to the destination.
 * 
 * See also getFileName(), isAccessible(), setName(), CException.
 * 
 * @param[in] to Destination path.
 * 
 * @exception CException - directory is not accessible.
 */
void CFile::moveFile(const string& to) const 
{
    string from = getFileName();

    if(!isAccessible(from))
    {
        throw CException(extxtf.IsNotAccessible);
    }

    string tmp = setName(to);

    rename(from.c_str(), tmp.c_str());
}