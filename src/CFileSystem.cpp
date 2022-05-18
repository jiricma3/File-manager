#include <filesystem>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <sys/ioctl.h>

#include "CFileSystem.h"

using namespace std;
using namespace std::filesystem;

vector<string> CFileSystem::m_Files;

void CFileSystem::printFileSystem() const
{
    string dirColor = "\033[38;2;0;140;212m";
    string fileColor = "\033[38;2;255;255;255m";
    string linkColor = "\033[38;2;210;0;200m";
    string resetColor = "\033[0m";

    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    int width = size.ws_col;
    int i = 0;

    loadFiles();

    sort(m_Files.begin(), m_Files.end());

    if(!m_Files.empty())
    {
        cout << setfill('-') << setw(width) << "\n";
    }

    for(const auto& it : m_Files)
    {
        if(is_directory(it))
        {
            cout << ++i << ".\t" << dirColor << it << resetColor << endl;
            cout << setfill('-') << setw(width) << "\n";
            continue;
        }

        if(is_symlink(it))
        {
            cout << ++i << ".\t" << linkColor << it << resetColor << endl;
            cout << setfill('-') << setw(width) << "\n";
            continue;
        }

        if(is_regular_file(it))
        {
            cout << ++i << ".\t" << fileColor << it << resetColor << endl;
            cout << setfill('-') << setw(width) << "\n";
            continue;
        }
    }
}

bool CFileSystem::changeDirectory(const string& to) const
{
    if(chdir(to.c_str()) != 0)
    {
        return false;
    }
    
    return true;
}

vector<string> & CFileSystem::getVector()
{
    return m_Files;
}

void CFileSystem::loadFiles() const
{
    string cur = current_path();

    m_Files.clear();

    for(const auto& it : directory_iterator(cur))
    {
       string z = it.path();
       string name = z.substr(z.find_last_of("/\\") + 1);

       m_Files.emplace_back(name);
    }
}
