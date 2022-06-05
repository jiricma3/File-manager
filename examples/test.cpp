#include <iostream>
#include <sstream>

#include "../src/CCommandProcess.h"

using namespace std;

int main()
{
    try
    {
        CLink d = CLink("hrhrhr", "jiricma3");
        CLink df = CLink("hrhrhrhrhrhrhrhrhrhrhrhr", "jiricma3");
        CLink dd = CLink("kjsdhskjdhksdhskdhrhr", "jiricma3");
        CLink ddi = CLink("kjsdhskjdhksdhskdhrhr", "jiricma3");
        CLink de = CLink("lksdlksd", "rererere");

        d.copyFile("goge");
        d.copyFile("goge");

        d.moveFile("jo");
        df.moveFile("ne");

        d.deleteFile();
        df.deleteFile();
        dd.deleteFile();
        de.deleteFile();
        df.deleteFile();
        d.deleteFile();

        CFile f = CFile("skjdksjdksjd");
        CFile fh = CFile("popopopop");
        CFile fe = CFile("popopopop");
        CFile fq = CFile("popopopop");
        CFile fk = CFile("popopopop");

        f.copyFile("kokkk");
        f.copyFile("kokkk");
        fh.copyFile("rereres");

        f.moveFile("ew");
        fh.moveFile("oppp");

        f.deleteFile();
        fh.deleteFile();
        f.deleteFile();

        CDir l = CDir("lklk");
        CDir le = CDir("pweopwoe");
        CDir lea = CDir("pweopwoe");
        CDir lek = CDir("pweopwoe");

        l.copyFile("lsssw");
        l.copyFile("lsssw");
        le.copyFile("wq");

        l.moveFile("lll");
        le.moveFile("mne");

        l.deleteFile();
        le.deleteFile();
        l.deleteFile();

        CFileSystem fs;
        fs.changeDirectory("Makefile");
        fs.changeDirectory("src");
        fs.changeDirectory("/home");
        fs.changeDirectory("/home/progtest/proseminare");
        fs.changeDirectory("sjdksjksjdksjd");

        fs.printFileSystem();
        fs.printFileSystemLong();

        CFile file = CFile("file");
        CDir dir = CDir("dir");
        CLink link = CLink("link", "file");

        CCreate cr;
        cr.doCom(file);
        cr.doCom(dir);
        cr.doCom(link);

        CCopy co;
        co.doCom(file, "file2");
        co.doCom(file, "file2");
        co.doCom(dir, "dir2");
        co.doCom(dir, "dir2");
        co.doCom(link, "link2");
        co.doCom(link, "link2");

        CMove mo;
        mo.doCom(file, "reFile");
        mo.doCom(file, "reFile");
        mo.doCom(dir, "reDir");
        mo.doCom(dir, "reDir");
        mo.doCom(link, "reLink");
        mo.doCom(link, "reLink");

        CDelete del;
        del.doCom(file);
        del.doCom(dir);
        del.doCom(link);

        CPrint pr;
        pr.doCom("../prohlaseni.txt");
        pr.doCom("kokokok");

        CList li;
        li.doCom(false);
        li.doCom(true);

        CWrite wr;
        wr.doCom("file2", "testovací text z kódu.");
        wr.doCom("lsjdlsdk", "text");

        CCurrent cu;
        cu.doCom();

        CChange ch;
        ch.doCom("../src");
        ch.doCom("kjfdkjfdkjffff");

        CMedia me;
        me.doCom();

        CHelp he;
        he.doCom();

        CCommandProcess c;
        vector<string> vec;

        vec.push_back("create");
        vec.push_back("-f");
        vec.push_back("testFile");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("create");
        vec.push_back("-f");
        c.passCommand(vec);
        vec.clear();
        
        vec.push_back("create");
        vec.push_back("-f");
        vec.push_back("testFile");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("create");
        vec.push_back("-d");
        vec.push_back("testDir");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("create");
        vec.push_back("-d");
        vec.push_back("testDir");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("create");
        vec.push_back("-l");
        vec.push_back("testLink");
        vec.push_back("testFile");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("create");
        vec.push_back("-l");
        vec.push_back("testFile");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("create");
        vec.push_back("-l");
        vec.push_back("testLink");
        vec.push_back("testFile");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("copy");
        vec.push_back("-r");
        vec.push_back("test.*");
        vec.push_back("ExtestLink2");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("copy");
        vec.push_back("testLink");
        vec.push_back("testLink2");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("copy");
        vec.push_back("testLink");
        vec.push_back("testLink2");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("copy");
        vec.push_back("testLink");
        vec.push_back("testLink2");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("copy");
        vec.push_back("testLinkneeeee");
        vec.push_back("testLink2");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("copy");
        vec.push_back("testFile");
        vec.push_back("testFile2");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("copy");
        vec.push_back("testDir");
        vec.push_back("testDir2");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("copy");
        vec.push_back("testLink");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("move");
        vec.push_back("-r");
        vec.push_back("test.*");
        vec.push_back("ReExtestLink2");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("move");
        vec.push_back("testLink");
        vec.push_back("RetestLink2");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("move");
        vec.push_back("testLink");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("move");
        vec.push_back("testLink");
        vec.push_back("RetestLink2");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("move");
        vec.push_back("testLink");
        vec.push_back("RetestLink2dfdfdfdf");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("move");
        vec.push_back("testFile");
        vec.push_back("RetestFile2");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("move");
        vec.push_back("testDir");
        vec.push_back("RetestDir2");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("delete");
        vec.push_back("-r");
        vec.push_back(".*Ex.*");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("delete");
        vec.push_back("RetestLink2");
        vec.push_back("RetestDir2");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("delete");
        vec.push_back("RetestLink2");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("delete");
        vec.push_back("RetestFile2");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("delete");
        vec.push_back("RetestDir2");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("print");
        vec.push_back("testLink2");
        vec.push_back("testLink2");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("print");
        vec.push_back("testLink2dsdsd");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("print");
        vec.push_back("testFile2");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("print");
        vec.push_back("testDir2");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("list");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("list");
        vec.push_back("-l");
        vec.push_back("-l");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("list");
        vec.push_back("-l");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("list");
        vec.push_back("-p");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("write");
        vec.push_back("testFile2");
        vec.push_back("test text 2");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("write");
        vec.push_back("testFile2");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("write");
        vec.push_back("testFile2ewewew");
        vec.push_back("test text 2");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("current");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("media");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("help");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("change");
        vec.push_back("../src");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("change");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("change");
        vec.push_back("../srcrererer");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("unknown");
        vec.push_back("testFile2");
        vec.push_back("test text 2");
        c.passCommand(vec);
        vec.clear();

        vec.push_back("end");
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

    return EXIT_SUCCESS;
}