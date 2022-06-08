#include <filesystem>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <iomanip>

#include "CFileSystem.h"

using namespace std;
using namespace std::filesystem;

vector<shared_ptr<CFileType>> CFileSystem::m_Vec;

/**
 * @brief Getting the current terminal width.
 * 
 * @return Terminal width.
 */
int getWidth()
{
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_col;
}

/**
 * @brief Printing a short listing of the contents of the directory to standard output.
 * 
 * See also getWidth(), loadFiles(), CFileType::getFileName(), CProperties.
 */
void CFileSystem::printFileSystem() const
{
    CProperties pr;
    
    int width = getWidth();
    int i = 0;

    loadFiles();

    sort(m_Vec.begin(), m_Vec.end(), [](const shared_ptr<CFileType>& l, const shared_ptr<CFileType>& r)
    {
        return l->getFileName() < r->getFileName();
    });

    if(!m_Vec.empty())
    {
        cout << setfill('-') << setw(width) << "\n";
    }

    for(const auto& it : m_Vec)
    {
        string file = it->getFileName();
        string name = file.substr(file.find_last_of("/\\") + 1);

        if(is_directory(file))
        {
            cout << ++i << ".\t" << pr.dirColor << name << pr.resetColor << endl;
            cout << setfill('-') << setw(width) << "\n";
            continue;
        }

        if(is_symlink(file))
        {
            cout << ++i << ".\t" << pr.linkColor << name << pr.resetColor << endl;
            cout << setfill('-') << setw(width) << "\n";
            continue;
        }

        if(is_regular_file(file))
        {
            cout << ++i << ".\t" << pr.fileColor << name << pr.resetColor << endl;
            cout << setfill('-') << setw(width) << "\n";
            continue;
        }
    }
}

/**
 * @brief Getting file attributes.
 * 
 * @param[in] it File name.
 * @param[in, out] st Pointer to struct stat.
 * @param[in, out] tim Character array with attributes.
 */
void getFileStats(const string& it, struct stat * st, char tim[80])
{
    stat(it.c_str(), st);
    time_t t = st->st_mtime;
    struct tm tm;
    localtime_r(&t, &tm);
    strftime(tim, 80, "%b %d %H:%M", &tm);
}

/**
 * @brief Printing a long, more detailed listing of the contents of the directory to standard output.
 * 
 * See also getWidth(), loadFiles(), CFileType::getFileName(), CProperties.
 */
void CFileSystem::printFileSystemLong() const
{
    CProperties pr;
    
    int width = getWidth();
    int i = 0;

    loadFiles();

    sort(m_Vec.begin(), m_Vec.end(), [](const shared_ptr<CFileType>& l, const shared_ptr<CFileType>& r)
    {
        return l->getFileName() < r->getFileName();
    });

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

        string file = it->getFileName();
        string name = file.substr(file.find_last_of("/\\") + 1);

        if(is_directory(file))
        {
            cout << ++i << ".\t" << (pw != 0 ? pw->pw_name : "unknown") << "\t" << (gr != 0 ? gr->gr_name : "unknown") <<
            "\t" << st.st_size << "\t   " << tim << "\t\t" << pr.dirColor << name << pr.resetColor << endl;
            cout << setfill('-') << setw(width) << "\n";
            continue;
        }

        if(is_symlink(file))
        {
            cout << ++i << ".\t" << (pw != 0 ? pw->pw_name : "unknown") << "\t" << (gr != 0 ? gr->gr_name : "unknown") <<
            "\t" << st.st_size << "\t   " << tim << "\t\t" << pr.linkColor << name << pr.resetColor << endl;
            cout << setfill('-') << setw(width) << "\n";
            continue;
        }

        if(is_regular_file(file))
        {
            cout << ++i << ".\t" << (pw != 0 ? pw->pw_name : "unknown") << "\t" << (gr != 0 ? gr->gr_name : "unknown") <<
            "\t" << st.st_size << "\t   " << tim << "\t\t" << pr.fileColor << name << pr.resetColor << endl;
            cout << setfill('-') << setw(width) << "\n";
            continue;
        }

        free(pw);
        free(gr);
    }
}

/**
 * @brief Changing the current directory.
 * 
 * After a successful directory change, its contents are listed.
 * 
 * Se also printFileSystem().
 * 
 * @param[in] to Directory path.
 * @return true - success.
 * @return false - failure.
 */
bool CFileSystem::changeDirectory(const string& to) const
{
    if(chdir(to.c_str()) != 0)
    {
        return false;
    }

    printFileSystem();
    
    return true;
}

/**
 * @brief Getting a reference to the vector of files.
 * 
 * @return Vector of files reference.
 */
vector<shared_ptr<CFileType>> & CFileSystem::getVector()
{
    return m_Vec;
}

/**
 * @brief Load files from the given path into the vector.
 * 
 * See also loadVector().
 * 
 * @param[in] path Source directory.
 */
void CFileSystem::loadFiles(const string& path) const
{
    loadVector(path);
}

/**
 * @brief Load files from the given path into the vector.
 * 
 * The method creates a new object for each file in the directory and then stores the pointer in a vector.
 * 
 * See also #m_Vec, CLink, CDir, CFile.
 * 
 * @param[in] path Source directory.
 */
void CFileSystem::loadVector(const string& path) const
{
    m_Vec.clear();

    string p = absolute(path);

    for(const auto& it : directory_iterator(p))
    {
        string name = it.path();

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

/**
 * @brief Load files from the current directory into the vector.
 * 
 * See also loadVector().
 */
void CFileSystem::loadFiles() const
{
    string cur = current_path();

    loadVector(cur);
}
