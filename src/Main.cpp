#include <iostream>
#include <sstream>

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
    CCommandProcess c;

    while(1)
    {
        fs.loadFiles();
        getline(cin, line);
        stringstream iss(line);
        int cnt = 0;

        while (iss >> word) 
        {   
            if(cnt == 0)
            {
                transform(word.begin(), word.end(), word.begin(), [](unsigned char c)
                {
                    return tolower(c);
                });
            }

            vec.push_back(word);
            cnt++;
        }

        try
        {
            c.passCommand(vec);
        }
        catch(const runtime_error& e)
        {
            return EXIT_SUCCESS;
        }
        catch(const CExeption& e)
        {
            cout << e.what() << endl;
        }
        
        vec.clear();
    }

    //cout << "\033[2J" << "\033[1;1H";

    return EXIT_SUCCESS;
}