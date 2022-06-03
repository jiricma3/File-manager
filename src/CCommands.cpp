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

ExTxt extxtc;

static map<ulong, string> types;

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

void CCreate::doCom(const CFileType& x) const
{
    x.createFile();
}

void CCopy::doCom(const CFileType& x, const string& to) const
{
    x.copyFile(to);
}

void CMove::doCom(const CFileType& x, const string& to) const
{
    x.moveFile(to);
}

void CDelete::doCom(const CFileType& x) const
{
    x.deleteFile();
}

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

void CPrint::doCom(const string& src) const
{
    ifstream f(src);

    if(access(src.c_str(), F_OK) != 0)
    {
        throw CExeption(extxtc.DoesntExist);
    }

    if(is_directory(src))
    {
        throw CExeption(extxtc.CouldNotPrint);
    }

    if(f.is_open() && !filesystem::is_empty(src))
    {
        cout << f.rdbuf() << endl;
    }
}

void CMedia::doCom() const
{
    space_info si = space("/home");
    fillTypes();
    string capB, freeB, usedB;

    struct statfs64 info;

    if(statfs64("/home", &info) != 0)
    {
        throw CExeption(extxtc.CouldNotGetFsInfo);
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

void CChange::doCom(const string& to) const
{
    CFileSystem fs;
    
    if(!fs.changeDirectory(to))
    {
        throw CExeption(extxtc.CouldNotChangeDir);
    }
}

void CHelp::doCom() const
{
    cout << "Usage: <command> [option] <source> <destination>\n\n";
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

void CCurrent::doCom() const
{
    string path = current_path();
    cout << "Current working directory: " << path << endl;
}

void CWrite::doCom(const string& path, const string& content) const
{
    ofstream file;
    file.open(path, ios::in | ios::app);

    if(!file.is_open())
    {
        throw CExeption(extxtc.CouldNotOpenFile);
    }
    else
    {
        file << content;
        file.close();
    }
}