#ifndef __CCOMMANDS_H__
#define __CCOMMANDS_H__

#include "CFile.h"
#include "CDir.h"
#include "CLink.h"
#include "CFileSystem.h"
#include "CCommandProcess.h"

using namespace std;

class CCommand
{   
    public:
        ~CCommand() = default;

    protected:
        CCommand(int opt) : m_Opt(opt) {}
        int getOpt() const { return m_Opt; }

    private:
        virtual void file() const = 0;
        virtual void dir() const = 0;
        virtual void link() const = 0;
        int m_Opt;
};

class CCreate : CCommand
{
    public:
        CCreate(int opt, const string& name, const string& target = "") : CCommand(opt), m_Name(name), m_Target(target) {}
        CCreate(const CCreate&) = delete;

        virtual void file() const override;
        virtual void dir() const override;
        virtual void link() const override;
        void help() const;

    private:
        string m_Name;
        string m_Target;
};

class CCopy : CCommand
{
    public:
        CCopy(int opt, const string& from, const string& to) : CCommand(opt), m_From(from), m_To(to) {}
        CCopy(const CCopy&) = delete;

        virtual void file() const override;
        virtual void dir() const override;
        virtual void link() const override;
        void help() const;
        
    private:
        string m_From;
        string m_To;
};

class CMove : CCommand
{
    public:
        CMove(int opt, const string& from, const string& to) : CCommand(opt), m_From(from), m_To(to) {}
        CMove(const CMove&) = delete;

        virtual void file() const override;
        virtual void dir() const override;
        virtual void link() const override;
        void help() const;
        
    private:
        string m_From;
        string m_To;
};

class CDelete : CCommand
{
    public:
        CDelete(int opt, const string& from) : CCommand(opt), m_From(from) {}
        CDelete(const CDelete&) = delete;

        virtual void file() const override;
        virtual void dir() const override;
        virtual void link() const override;
        void help() const;
        
    private:
        string m_From;
};

class CPrint
{
    public:
        CPrint(const string& name) : m_Name(name) {}
        CPrint(const CPrint&) = delete;
        ~CPrint() = default;
        void help() const;
        void print() const;

    private:
        string m_Name;
};

class CList
{
    public:
        CList(int opt = -1) : m_Opt(opt) {}
        CList(const CList&) = delete;
        ~CList() = default;
        void list() const;
        void help() const;
    
    private:
        int m_Opt;
};

class CMedia
{
    public:
        CMedia() { media(); }
        CMedia(const CMedia&) = delete;
        ~CMedia() = default;
        void help() const;
        void media() const;
};

class CChange
{
    public:
        CChange(const string& to) : m_To(to) {}
        CChange() = default;
        CChange(const CChange&) = delete;
        ~CChange() = default;
        void help() const;
        void change() const;

    private:
        string m_To;
};

class CHelp
{
    public:
        CHelp() { help(); }
        CHelp(const CHelp&) = delete;
        ~CHelp() = default;
        void help() const;
};

#endif