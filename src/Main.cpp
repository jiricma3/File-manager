#include <iostream>
#include <sstream>

#include "CFile.h"
#include "CFileSystem.h"
#include "CDir.h"
#include "CLink.h"
#include "CCommandProcess.h"

using namespace std;

int main()
{
    CLink d = CLink("hrhrhr", "jiricma3");
    // CLink df = CLink("hrhrhrhrhrhrhrhrhrhrhrhr", "jiricma3");
    // CLink dd = CLink("kjsdhskjdhksdhskdhrhr", "jiricma3");
    // d.copyFileRegex(".*hr", "jjj");
    // d.deleteFileRegex(".*jj[a-z]");
    // d.deleteFileRegex(".*hr");

    CFileSystem fs;
    // fs.changeDirectory("Makefile");
    // fs.changeDirectory("src");
    // fs.changeDirectory("/home");
    // fs.changeDirectory("/home/progtest/proseminare");

    fs.printFileSystem();
    
    CCommandProcess("create", "f", "kkkkkk");
    CCommandProcess("print", "prohlaseni.txt");
    CCommandProcess("copy", "f", "kkkkkk", "ruru");
    CCommandProcess("move", "f", "kkkkkk", "src/gg");
    CCommandProcess("media");
    CCommandProcess("delete", "f", "ruru");
    CCommandProcess("change", "src");
    CCommandProcess("list", "ll");
    CCommandProcess("list");
    CCommandProcess("help");
    CCommandProcess("end");
    string f, l;
    vector<string> vec;

    getline(cin, f);
    stringstream iss(f);

    while ( iss >> l) 
    {    
        vec.push_back(l);
    }

    //cout << "\033[2J" << "\033[1;1H";
    cout << "\n\n\n";
    fs.printFileSystem();
    

    return EXIT_SUCCESS;
}