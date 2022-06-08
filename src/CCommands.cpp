#include <iostream>
#include <fstream>
#include <unistd.h>
#include <filesystem>
#include <sys/vfs.h>
#include <map>
#include <iomanip>

#include "CCommands.h"

using namespace std;
using namespace std::filesystem;

CExTxt extxtc; ///< Instance of the error messages class.

static map<ulong, string> types; ///< Stored file system names according to unique identifiers.

/**
 * @brief Filling map with file system types.
 * 
 */
void fillTypes()
{
    types[0x9660] = "ISOFS";
    types[0xEF53] = "EXT4";
    types[0x4d44] = "MSDOS";
    types[0x6969] = "NFS";
    types[0x5346544e] = "NTFS";
    types[0x9fa2] = "USB";
    types[0x517B] = "SMB";
}

/**
 * @brief Getting the unit size.
 * 
 * @param[in] i Number of thousands.
 * 
 * @return Unit.
 */
string getExt(int i)
{
    switch (i)
    {
        case 0:
                return "B";
            break;

        case 1:
                return "KB";
            break;
            
        case 2:
                return "MB";
            break;
            
        case 3:
                return "GB";
            break;
            
        case 4:
                return "TB";
            break;
        
        default:
                return "NaN";
            break;
    }
}

/**
 * @brief Shorten the number to the largest possible unit.
 * 
 * See also getExt().
 * 
 * @param[in, out] ext Unit.
 * @param[in] size Size.
 * 
 * @return The shortest possible number.
 */
double getSize(string& ext, ulong size)
{
    double tmp = size;
    int i = 0;

    for(; tmp > 1000; i++)
    {
        tmp = tmp / 1000;
    }

    ext = getExt(i);

    return tmp;
}

/**
 * @brief Call the creation of the required file.
 * 
 * See also CFile::createFile(), CDir::createFile(), CLink::createFile().
 * 
 * @param[in] x Specified file type by user input.
 */
void CCreate::doCom(const CFileType& x) const
{
    x.createFile();
}

/**
 * @brief Calling the desired file to copy to the destination path.
 * 
 * See also CFile::copyFile(), CDir::copyFile(), CLink::copyFile().
 * 
 * @param[in] x Specified file type by user input.
 * @param[in] to Specified file path.
 */
void CCopy::doCom(const CFileType& x, const string& to) const
{
    x.copyFile(to);
}

/**
 * @brief Calling the desired file to move to the destination path.
 * 
 * See also CFile::moveFile(), CDir::moveFile(), CLink::moveFile().
 * 
 * @param[in] x Specified file type by user input.
 * @param[in] to Specified file path.
 */
void CMove::doCom(const CFileType& x, const string& to) const
{
    x.moveFile(to);
}

/**
 * @brief Calling the deletion of the required file.
 * 
 * See also CFile::deleteFile(), CDir::deleteFile(), CLink::deleteFile().
 * 
 * @param[in] x Specified file type by user input.
 */
void CDelete::doCom(const CFileType& x) const
{
    x.deleteFile();
}

/**
 * @brief Calling the directory content listing.
 * 
 * See also CFileSystem, CFileSystem::printFileSystem(), CFileSystem::printFileSystemLong().
 * 
 * @param[in] l Listing a long or short statement. 
 */
void CList::doCom(bool l) const
{
    CFileSystem fs;

    if(!l)
    {
        fs.printFileSystem();
    }
    else
    {
        fs.printFileSystemLong();
    }
}

/**
 * @brief The regular file content listing.
 * 
 * If the file is accessible, not a directory and is not empty, its contents are written to standard output.
 * 
 * Se also CException.
 * 
 * @param[in] src File path.
 * 
 * @exception CException - source file does not exist.
 * @exception CException - source file is a directory.
 */
void CPrint::doCom(const string& src) const
{
    ifstream f(src);

    if(access(src.c_str(), F_OK) != 0)
    {
        throw CException(extxtc.DoesntExist);
    }

    if(is_directory(src))
    {
        throw CException(extxtc.CouldNotPrint);
    }

    if(f.is_open() && !filesystem::is_empty(src))
    {
        cout << f.rdbuf() << endl;
    }
}

/**
 * @brief Listing information about the storage.
 * 
 * See also fillTypes(), getSize(), CException.
 * 
 * @exception CException - unable to get filesystem information.
 */
void CMedia::doCom() const
{
    space_info si = space("/home");
    fillTypes();
    string capB, freeB, usedB;

    struct statfs64 info;

    if(statfs64("/home", &info) != 0)
    {
        throw CException(extxtc.CouldNotGetFsInfo);
    }

    double cap = getSize(capB, si.capacity);
    double free = getSize(freeB, si.free);
    double used = getSize(usedB, si.capacity - si.free);
    
    cout << setfill('-') << setw(34) << fixed << setprecision(2) << "\n";
    cout << "| " << "Filesystem type: " << types[info.f_type] << "\t\t|" << endl;
    cout << "| " << "Disk capacity: " << cap << " " << capB << "\t|" << endl;
    cout << "| " << "Used space: " << used << " " << usedB << "\t\t|" << endl;
    cout << "| " << "Free space: " << free << " " << freeB << "\t\t|" << endl;
    cout << setfill('-') << setw(34) << "\n";
    cout << flush;
}

/**
 * @brief Change working directory.
 * 
 * See also CFileSystem, CFileSystem::changeDirectory(), CException.
 * 
 * @param[in] to Directory path.
 * 
 * @exception CException - unable to change directory.
 */
void CChange::doCom(const string& to) const
{
    CFileSystem fs;
    
    if(!fs.changeDirectory(to))
    {
        throw CException(extxtc.CouldNotChangeDir);
    }
}

/**
 * @brief Listing the help menu.
 * 
 */
void CHelp::doCom() const
{
    cout << "Usage:\t<command> [option] {source} {destination}\n";
    cout << "\t<command> [option] {file}\n";
    cout << "\t<command> [option]\n";
    cout << "\t<command> {file}\n";
    cout << "\t<command>\n\n";
    cout << "Commands:\n" << "\tcreate  -  Options: -f\tParams(1): 1. Path to create a file.   Description: Create regular file.\n";
    cout << "\t\t\t    -d\tParams(1): 1. Path to create a directory.   Description: Create directory.\n";
    cout << "\t\t\t    -l\tParams(2): 1. Path to create a symlink, 2. Target file.   Description: Create symbolic link.\n\n";
    cout << "\tcopy  -  Options: -r  Params(2): 1. Regular expression for source file(s), 2. Destination.   Description: Copy file(s) using regular expression to given path.\n";
    cout << "\tcopy  -  Params(2): 1. Source file, 2. Destination.   Description: Copy file to given path.\n\n";
    cout << "\tmove  -  Options: -r  Params(2): 1. Regular expression for source file(s), 2. Destination.   Description: Move file(s) using regular expression to given path.\n";
    cout << "\tmove  -  Params(2): 1. Source file, 2. Destination.   Description: Move file to given path.\n\n";
    cout << "\tdelete  -  Options: -r  Params(1): 1. Regular expression for file(s).   Description: Delete file(s) using regular expression.\n";
    cout << "\tdelete  -  Params(1): 1. Source file.   Description: Delete file.\n\n";
    cout << "\tprint  -  Params(1): 1. Path to regular file.   Description: Print content of regular file.\n\n";
    cout << "\twrite  -  Params(2): 1. File path, 2. Text.   Description: Write given text to file.\n\n";
    cout << "\tlist  -  Options: -l  Description: Print advanced file information in a directory.\n";
    cout << "\tlist  -  Description: Print basic file information in a directory.\n\n";
    cout << "\tchange  -  Params(1): 1. Directory path.   Description: Change working directory.\n\n";
    cout << "\tmedia  -  Description: Print filesystem information.\n\n";
    cout << "\tcurrent  -  Description: Print current working diretory.\n\n";
    cout << "\thelp  -  Description: Print this help text.\n\n";
    cout << "\tend  -  Description: Exit program." << endl;
}

/**
 * @brief Listing the current working directory.
 * 
 */
void CCurrent::doCom() const
{
    string path = current_path();
    cout << "Current working directory: " << path << endl;
}

/**
 * @brief Writing text to a file.
 * 
 * See also CException.
 * 
 * @param[in] path File path.
 * @param[in] content Text to write.
 * 
 * @exception CException - could not open file.
 */
void CWrite::doCom(const string& path, const string& content) const
{
    ofstream file;
    file.open(path, ios::in | ios::app);

    if(!file.is_open())
    {
        throw CException(extxtc.CouldNotOpenFile);
    }
    else
    {
        file << content;
        file.close();
    }
}

/**
 * @brief Error message listing.
 * 
 */
void CError::doCom() const
{
    cout << "Unknown command. Type \"help\" for help menu." << endl;
}