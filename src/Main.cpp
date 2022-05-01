#include "CFile.h"
#include "CFileSystem.h"
#include "CDir.h"
#include "CLink.h"

int main()
{
    CFile f = CFile("r");
    CLink l = CLink("zrzrzzr", "r");
    l.copyFile("ee");
    l.moveFile("ttrtrr");
    l.deleteFile();
    l.deleteFile("ttrtrr");

    return EXIT_SUCCESS;
}