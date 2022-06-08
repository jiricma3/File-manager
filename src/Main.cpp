#include <iostream>
#include <sstream>
#include <iomanip>

#include "CCommandProcess.h"

using namespace std;

/**
 * @brief Function for data collection from standard input.
 * 
 * See also CFileSystem::printFileSystem(), CFileSystem::loadFiles(), CCommandProcess::passCommand(), CException::what(), CFileSystem, CCommandProcess, CException.
 * 
 * @return Exit value.
 */
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
        catch(const CException& e)
        {
            cout << e.what() << endl;
        }
        
        vec.clear();
    }

    return EXIT_SUCCESS;
}