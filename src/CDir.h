#include <string>

#include "CFileType.h"

using namespace std;

class CDir : public CFileType
{
    public:
        bool createFile(const string& name) override;
        bool copyFile(const string& to) override;
        bool deleteFile() override;
        //bool changeDirectory(const string& to) override;
        bool moveFile(const string& to) override;
        CFileType * cloneFile() const override;

    protected:
        CDir(const string& name) : CFileType(name, 4096) {}
};