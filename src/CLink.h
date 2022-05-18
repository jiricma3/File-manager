#ifndef __CLINK_H__
#define __CLINK_H__

#include "CFileType.h"

using namespace std;

class CLink : public CFileType
{
    public:
        CLink() = default;
        CLink(const string& name, const string& target) : CFileType(name), m_Target(target) { createLink(m_Target); }
        virtual bool createFile() const override { return true; }
        bool createLink(const string& target) const;
        bool createLink(const string& target, const string& expression) const;
        virtual bool copyFile(const string& to) const override;
        virtual bool copyFile(const string& from, const string& to) const override;
        virtual bool copyFileRegex(const string& expression, const string& to) const override;
        virtual bool deleteFile() const override;
        virtual bool deleteFile(const string& src) const override;
        virtual bool deleteFileRegex(const string& expression) const override;
        virtual bool moveFile(const string& to) const override;
        virtual bool moveFile(const string& from, const string& to) const override;
        virtual bool moveFileRegex(const string& expression, const string& to) const override;
        CFileType * cloneFile() const;

    private:
        string m_Target;
};

#endif 