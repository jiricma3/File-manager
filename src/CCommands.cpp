#include <iostream>
#include <fstream>
#include <filesystem>
#include <sys/vfs.h>
#include <map>

#include "CCommands.h"

using namespace std;
using namespace std::filesystem;

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

void CCopy::doCom(const CFileType& x, const string& from, const string& to) const
{
    x.copyFile(from, to);
}

void CMove::doCom(const CFileType& x, const string& from, const string& to) const
{
    x.moveFile(from, to);
}

void CDelete::doCom(const CFileType& x, const string& from) const
{
    x.deleteFile(from);
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

    if(f.is_open())
    {
        cout << f.rdbuf();
    }
}

void CMedia::doCom() const
{
    space_info si = space("/home");
    fillTypes();
    string capB, freeB, usedB;

    struct statfs64 info;

    statfs64("/home", &info);

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
    fs.changeDirectory(to);
}

void CHelp::doCom() const
{
    cout << "help todo" << endl;
}