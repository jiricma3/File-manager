#include <string>

#include "CFileType.h"

using namespace std;

std::size_t CFileType::getFileSize() const
{
    return m_Size;
}

string & CFileType::getFileName()
{
    return m_Name;
}
