#include <filesystem>
#include <regex>

#include "CFileType.h"

using namespace std;
using namespace std::filesystem;

const string & CFileType::getFileName() const
{
    return m_Name;
}

const string CFileType::setPath() const 
{
    string cp = current_path();
    cp.append("/" + m_Name);
    return cp;
}