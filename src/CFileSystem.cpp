#include <filesystem>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

#include "CFileSystem.h"

using namespace std;
using namespace std::filesystem;

vector<shared_ptr<CFileType>> CFileSystem::m_Vec;

struct Properties
{
    Properties() = default;
    string dirColor = "\033[38;2;0;140;212m";
    string fileColor = "\033[38;2;255;255;255m";
    string linkColor = "\033[38;2;210;0;200m";
    string resetColor = "\033[0m";
};

int getWidth()
{
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_col;
}

void CFileSystem::printFileSystem() const
{
    Properties pr;
    
    int width = getWidth();
    int i = 0;

    loadFiles();

    sort(m_Vec.begin(), m_Vec.end());

    if(!m_Vec.empty())
    {
        cout << setfill('-') << setw(width) << "\n";
    }

    for(const auto& it : m_Vec)
    {
        if(is_directory(it->getFileName()))
        {
            cout << ++i << ".\t" << pr.dirColor << it->getFileName() << pr.resetColor << endl;
            cout << setfill('-') << setw(width) << "\n";
            continue;
        }

        if(is_symlink(it->getFileName()))
        {
            cout << ++i << ".\t" << pr.linkColor << it->getFileName() << pr.resetColor << endl;
            cout << setfill('-') << setw(width) << "\n";
            continue;
        }

        if(is_regular_file(it->getFileName()))
        {
            cout << ++i << ".\t" << pr.fileColor << it->getFileName() << pr.resetColor << endl;
            cout << setfill('-') << setw(width) << "\n";
            continue;
        }
    }
}

void getFileStats(const string& it, struct stat * st, char tim[80])
{
    stat(it.c_str(), st);
    time_t t = st->st_mtime;
    struct tm tm;
    localtime_r(&t, &tm);
    strftime(tim, 80, "%b %d %H:%M", &tm);
}

void CFileSystem::printFileSystemLong() const
{
    Properties pr;
    
    int width = getWidth();
    int i = 0;

    loadFiles();

    sort(m_Vec.begin(), m_Vec.end());

    struct stat st;

    if(!m_Vec.empty())
    {
        cout << setfill('-') << setw(width) << "\n";
    }

    for(const auto& it : m_Vec)
    {
        char tim[80];
        getFileStats(it->getFileName(), &st, tim);
        struct passwd * pw = getpwuid(st.st_uid);
        struct group * gr = getgrgid(st.st_gid);

        if(is_directory(it->getFileName()))
        {
            cout << ++i << "\t" << (pw != 0 ? pw->pw_name : "no owner") << "\t" << (gr != 0 ? gr->gr_name : "no group") <<
            "\t" << st.st_size << "\t   " << tim << "\t\t" << pr.dirColor << it->getFileName() << pr.resetColor << endl;
            cout << setfill('-') << setw(width) << "\n";
            continue;
        }

        if(is_symlink(it->getFileName()))
        {
            cout << ++i << "\t" << (pw != 0 ? pw->pw_name : "no owner") << "\t" << (gr != 0 ? gr->gr_name : "no group") <<
            "\t" << st.st_size << "\t   " << tim << "\t\t" << pr.linkColor << it->getFileName() << pr.resetColor << endl;
            cout << setfill('-') << setw(width) << "\n";
            continue;
        }

        if(is_regular_file(it->getFileName()))
        {
            cout << ++i << "\t" << (pw != 0 ? pw->pw_name : "no owner") << "\t" << (gr != 0 ? gr->gr_name : "no group") <<
            "\t" << st.st_size << "\t   " << tim << "\t\t" << pr.fileColor << it->getFileName() << pr.resetColor << endl;
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

    printFileSystem();
    
    return true;
}

vector<shared_ptr<CFileType>> & CFileSystem::getVector()
{
    return m_Vec;
}

void CFileSystem::loadFiles() const
{
    string cur = current_path();

    m_Vec.clear();

    for(const auto& it : directory_iterator(cur))
    {
       string z = it.path();
       string name = z.substr(z.find_last_of("/\\") + 1);

       if(is_directory(name))
       {
           CDir * c = new CDir(name);
           m_Vec.emplace_back(c);
           continue;
       }

       if(is_symlink(name))
       {
           string target = read_symlink(name);
           CLink * c = new CLink(name, target);
           m_Vec.emplace_back(c);
           continue;
       }

       if(is_regular_file(name))
       {
           CFile * c = new CFile(name);
           m_Vec.emplace_back(c);
       }
    }
}
