#ifndef __CCOMMANDS_H__
#define __CCOMMANDS_H__

#include "CFileType.h"
#include "CFileSystem.h"
#include "CExeption.h"

using namespace std;

class CCommand
{
    public:
        virtual ~CCommand() = default;
        virtual void doCom(const CFileType&, const string&, const string&) const {}
        virtual void doCom(const CFileType&, const string&) const {}
        virtual void doCom(const CFileType&) const {}
        virtual void doCom(bool l) const {}
        virtual void doCom() const {}
        virtual void doCom(const string&) const {}
        virtual void doCom(const string&, const string&) const {}
};

class CCreate : public CCommand
{
    public:
        CCreate() = default;
        CCreate(const CCreate&) = delete;
        virtual void doCom(const CFileType&) const override;
};

class CCopy : public CCommand
{
    public:
        CCopy() = default;
        CCopy(const CCopy&) = delete;
        virtual void doCom(const CFileType&, const string&) const override;
};

class CMove : public CCommand
{
    public:
        CMove() = default;
        CMove(const CMove&) = delete;
        virtual void doCom(const CFileType&, const string&) const override;
};

class CDelete : public CCommand
{
    public:
        CDelete() = default;
        CDelete(const CDelete&) = delete;
        virtual void doCom(const CFileType&) const override;
};

class CPrint : public CCommand
{
    public:
        CPrint() = default;
        CPrint(const CPrint&) = delete;
        virtual void doCom(const string&) const override;
};

class CList : public CCommand
{
    public:
        CList() = default;
        CList(const CList&) = delete;
        virtual void doCom(bool) const override;
};

class CMedia : public CCommand
{
    public:
        CMedia() = default;
        CMedia(const CMedia&) = delete;
        virtual void doCom() const override;
};

class CChange : public CCommand
{
    public:
        CChange() = default;
        CChange(const CChange&) = delete;
        virtual void doCom(const string&) const override;
};

class CHelp : public CCommand
{
    public:
        CHelp() = default;
        CHelp(const CHelp&) = delete;
        virtual void doCom() const override;
};

class CCurrent : public CCommand
{
    public:
        CCurrent() = default;
        CCurrent(const CCurrent&) = delete;
        virtual void doCom() const override;
};

class CWrite : public CCommand
{
    public:
        CWrite() = default;
        CWrite(const CWrite&) = delete;
        virtual void doCom(const string&, const string&) const override;
};

#endif