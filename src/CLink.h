#ifndef __CLINK_H__
#define __CLINK_H__

#include <string>

#include "CFileType.h"

using namespace std;

class CLink : public CFileType
{
    public:
        CLink(const string& name, const string& target) : CFileType(name), m_Target(target) { createLink(m_Target); }
        virtual bool createFile() override { return true; }
        bool createLink(const string& target);
        virtual bool copyFile(const string& to) override;
        virtual bool copyFile(const string& from, const string& to) override;
        virtual bool deleteFile() override;
        virtual bool deleteFile(const string& src) override;
        virtual bool moveFile(const string& to) override;
        virtual bool moveFile(const string& from, const string& to) override;
        CFileType * cloneFile() const;

    private:
        string m_Target;
};

#endif 