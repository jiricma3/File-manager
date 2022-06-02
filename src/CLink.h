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
        virtual void createFile() const override { createLink(m_Target); }
        void createLink(const string&) const;
        virtual void copyFile(const string&) const override;
        virtual void deleteFile() const override;
        virtual void moveFile(const string&) const override;

    private:
        string m_Target;
};

#endif 