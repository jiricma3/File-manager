#include <iostream>
#include <sstream>
#include <iomanip>

#include "CCommandProcess.h"

using namespace std;

int main()
{
    CFileSystem fs;
    string word, line;
    vector<string> vec;
    CCommandProcess c;

    fs.printFileSystem();

    while(true)
    {
        fs.loadFiles();
        getline(cin, line);
        stringstream iss(line);

        while (iss >> quoted(word))
        {   
            vec.push_back(word);
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

    return EXIT_SUCCESS;
}