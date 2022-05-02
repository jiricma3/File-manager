#include "CFile.h"
#include "CFileSystem.h"
#include "CDir.h"
#include "CLink.h"

int main()
{
    CFile f = CFile("r");
    f.copyFile("rrr");
    CLink l = CLink("we", "r");
    CLink lg = CLink("we", "re");
    l.copyFile("r");
    l.copyFile("we", "r");
    l.copyFile("r");
    l.moveFile("tt");
    l.moveFile("r", "tt");

    return EXIT_SUCCESS;
}