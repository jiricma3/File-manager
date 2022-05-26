#ifndef __CLINK_H__
#define __CLINK_H__

#include "CFileType.h"

using namespace std;

class CLink : public CFileType
{
    public:
        CLink() = default;
        CLink(const string& name, const string& target) : CFileType(name), m_Target(target) {}
        virtual const string setName(const string&) const override;
        virtual bool createFile() const override { return createLink(m_Target) == true ? true : false; }
        bool createLink(const string&) const;
        virtual bool copyFile(const string&, const string&) const override;
        virtual bool deleteFile(const string&) const override;
        virtual bool moveFile(const string&, const string&) const override;

    private:
        string m_Target;
};

#endif 