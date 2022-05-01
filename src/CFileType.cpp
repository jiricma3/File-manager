#include  <filesystem>

#include "CFileType.h"

using namespace std;
using namespace std::filesystem;

string & CFileType::getFileName()
{
    return m_Name;
}


string CFileType::setPath()
{
    string cp = current_path();
    cp.append("/" + m_Name);
    return cp;
}

