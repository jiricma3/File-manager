#include <iostream>
#include <sstream>

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
        int cnt = 0;

        while (iss >> quoted(word)) 
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

    return EXIT_SUCCESS;
}