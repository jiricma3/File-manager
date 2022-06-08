#ifndef __CCOMMANDS_H__
#define __CCOMMANDS_H__

#include "CFileSystem.h"

using namespace std;

/**
 * @brief Parent class for all supported commands.
 * 
 * Contains virtual methods that are overridden in derived classes.
 * 
 */
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

/**
 * @brief Class for the create command.
 * 
 * Creates the desired file on disk.
 * 
 */
class CCreate : public CCommand
{
    public:
        CCreate() = default;
        CCreate(const CCreate&) = delete;
        virtual void doCom(const CFileType&) const override;
};

/**
 * @brief Class for the copy command.
 * 
 * Copies files from location A to location B.
 * 
 */
class CCopy : public CCommand
{
    public:
        CCopy() = default;
        CCopy(const CCopy&) = delete;
        virtual void doCom(const CFileType&, const string&) const override;
};

/**
 * @brief Class for the move command.
 * 
 * Moves files from location A to location B
 * 
 */
class CMove : public CCommand
{
    public:
        CMove() = default;
        CMove(const CMove&) = delete;
        virtual void doCom(const CFileType&, const string&) const override;
};

/**
 * @brief Class for the delete command.
 * 
 * Deletes files from the specified path.
 * 
 */
class CDelete : public CCommand
{
    public:
        CDelete() = default;
        CDelete(const CDelete&) = delete;
        virtual void doCom(const CFileType&) const override;
};

/**
 * @brief Class for the print command.
 * 
 * Lists the file contents.
 * 
 */
class CPrint : public CCommand
{
    public:
        CPrint() = default;
        CPrint(const CPrint&) = delete;
        virtual void doCom(const string&) const override;
};

/**
 * @brief Class for the list command.
 * 
 * Lists the directory contents.
 * 
 */
class CList : public CCommand
{
    public:
        CList() = default;
        CList(const CList&) = delete;
        virtual void doCom(bool) const override;
};

/**
 * @brief Class for the media command.
 * 
 * Lists disk space usage information.
 * 
 */
class CMedia : public CCommand
{
    public:
        CMedia() = default;
        CMedia(const CMedia&) = delete;
        virtual void doCom() const override;
};

/**
 * @brief Class for the change command.
 * 
 * Changes the current working directory.
 * 
 */
class CChange : public CCommand
{
    public:
        CChange() = default;
        CChange(const CChange&) = delete;
        virtual void doCom(const string&) const override;
};

/**
 * @brief Class for the help command.
 * 
 * Lists the help menu.
 * 
 */
class CHelp : public CCommand
{
    public:
        CHelp() = default;
        CHelp(const CHelp&) = delete;
        virtual void doCom() const override;
};

/**
 * @brief Class for the current command.
 * 
 * Lists the current directory in which the user is located.
 * 
 */
class CCurrent : public CCommand
{
    public:
        CCurrent() = default;
        CCurrent(const CCurrent&) = delete;
        virtual void doCom() const override;
};

/**
 * @brief Class for the write command.
 * 
 * Writes text to a file.
 * 
 */
class CWrite : public CCommand
{
    public:
        CWrite() = default;
        CWrite(const CWrite&) = delete;
        virtual void doCom(const string&, const string&) const override;
};

/**
 * @brief Error class for indicating unknown commands.
 * 
 * Resolves unknown commands.
 * 
 */
class CError : public CCommand
{
    public:
        CError() = default;
        CError(const CError&) = delete;
        virtual void doCom() const override;
};

#endif