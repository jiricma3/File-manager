#ifndef __CCOMMANDS_H__
#define __CCOMMANDS_H__

#include "CFile.h"
#include "CDir.h"
#include "CLink.h"
#include "CFileSystem.h"

using namespace std;

class CCommand
{   
    public:
        virtual ~CCommand() = default;
        virtual void doCom(const CFileType& x, const string& from, const string& to) const {}
        virtual void doCom(const CFileType& x) const {}
        //virtual void help() const;

    protected:
        CCommand() = default;
        CCommand(int opt) : m_Opt(opt) {}
        int getOpt() const { return m_Opt; }

    private:
        int m_Opt;
};

class CCreate : public CCommand
{
    public:
        CCreate() = default;
        CCreate(const string& name, const string& target = "") : m_Name(name), m_Target(target) {}
        CCreate(const CCreate&) = delete;
        //virtual void help() const override;
        virtual void doCom(const CFileType& x) const override;

    private:
        string m_Name;
        string m_Target;
};

class CCopy : public CCommand
{
    public:
        CCopy(int opt, const string& from, const string& to) : CCommand(opt), m_From(from), m_To(to) {}
        CCopy() = default;
        CCopy(const CCopy&) = delete;
        void help() const;
        virtual void doCom(const CFileType& x, const string& from, const string& to) const override;
        
    private:
        string m_From;
        string m_To;
};

class CMove : public CCommand
{
    public:
        CMove(int opt, const string& from, const string& to) : CCommand(opt), m_From(from), m_To(to) {}
        CMove(const CMove&) = delete;
        void help() const;
        virtual void doCom(const CFileType& x, const string& from, const string& to) const override;
        
    private:
        string m_From;
        string m_To;
};

class CDelete : public CCommand
{
    public:
        CDelete(int opt, const string& from) : CCommand(opt), m_From(from) {}
        CDelete(const CDelete&) = delete;
        void help() const;
        virtual void doCom(const CFileType& x, const string& from, const string& to) const override;
        
    private:
        string m_From;
};

class CPrint : public CCommand
{
    public:
        CPrint() = default;
        CPrint(const string& name) : m_Name(name) {}
        CPrint(const CPrint&) = delete;
        void help() const;
        void print() const;
        virtual void doCom(const CFileType& x) const override;

    private:
        string m_Name;
};

class CList : public CCommand
{
    public:
        CList() = default;
        CList(int opt = -1) : CCommand(opt) {}
        CList(const CList&) = delete;
        void list() const;
        void help() const;
        virtual void doCom(const CFileType& x) const override;
};

class CMedia : public CCommand
{
    public:
        CMedia() { media(); }
        CMedia(const CMedia&) = delete;
        void help() const;
        void media() const;
        virtual void doCom(const CFileType& x) const override;
};

class CChange : public CCommand
{
    public:
        CChange(const string& to) : m_To(to) {}
        CChange() = default;
        CChange(const CChange&) = delete;
        void help() const;
        void change() const;
        virtual void doCom(const CFileType& x) const override;

    private:
        string m_To;
};

class CHelp : public CCommand
{
    public:
        CHelp() { help(); }
        CHelp(const CHelp&) = delete;
        void help() const;
        virtual void doCom(const CFileType& x) const override;
};

#endif