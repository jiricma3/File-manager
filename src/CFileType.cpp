#include <filesystem>

#include "CFileType.h"

using namespace std;
using namespace std::filesystem;

/**
 * @brief Getting the file name.
 * 
 * @return File name.
 */
const string & CFileType::getFileName() const
{
    return m_Name;
}

/**
 * @brief File path adjustment.
 * 
 * The resulting path to the file is created by associating its name with the directory where it is stored.
 * 
 * @return File path.
 */
const string CFileType::setPath() const 
{
    string cp = current_path();
    cp.append("/" + m_Name);
    return cp;
}