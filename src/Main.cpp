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
    //CLink d = CLink("hrhrhr", "jiricma3");
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
    
    // CCommandProcess("creasddte", "f", "kkkkkk");
    // CCommandProcess("creasddte", "f", "kkkkkk");
    // CCommandProcess("creasddte", "f", "kkkkkk");
    // CCommandProcess("creasddte", "f", "kkkkkk");
    // CCommandProcess("print", "prohlaseni.txt");
    // CCommandProcess("copy", "t", "kkkkkk", "ruru");
    // CCommandProcess("move", "f", "kkkkkk", "src/gg");
    // CCommandProcess("media");
    // CCommandProcess("delete", "f", "ruru");
    // CCommandProcess("change", "src");
    // CCommandProcess("list", "ll");
    // CCommandProcess("list");
    // CCommandProcess("help");
    // CCommandProcess("end");
    string word, line;
    vector<string> vec;

    while(1)
    {
        fs.loadFiles();
        getline(cin, line);
        stringstream iss(line);

        while (iss >> word) 
        {   
            transform(word.begin(), word.end(), word.begin(), [](unsigned char c)
            {
                return tolower(c);
            });

            vec.push_back(word);
        }

        try
        {
            CCommandProcess c = CCommandProcess(vec);
        }
        catch(const std::exception& e)
        {
            return EXIT_SUCCESS;
        }
        
        
        vec.clear();
    }

    //cout << "\033[2J" << "\033[1;1H";

    return EXIT_SUCCESS;
}