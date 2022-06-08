#include <map>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include "CCommandProcess.h"

using namespace std;

CExTxt exTxt; ///< Instance of the error messages class.

vector<string> opts; ///< Vector containing all possible command options.
vector<string> vec; ///< Vector containing all possible commands.

/**
 * @brief Fulfillment of the vector with supported commands.
 * 
 */
void initCom()
{
    vec.push_back("create");
    vec.push_back("copy");
    vec.push_back("move");
    vec.push_back("delete");
    vec.push_back("print");
    vec.push_back("list");
    vec.push_back("change");
    vec.push_back("media");
    vec.push_back("help");
    vec.push_back("end");
    vec.push_back("current");
    vec.push_back("write");
}

/**
 * @brief Fulfillment of the vector with supported command options.
 * 
 */
void initOpt()
{
    opts.push_back("-r");
    opts.push_back("-f");
    opts.push_back("-d");
    opts.push_back("-l");
}

/**
 * @brief Determining the specified option.
 * 
 * See also initOpt().
 * 
 * The option vector is iterated, and if an option has been specified, the method returns the numeric value of the option.
 * If not, a value indicating a command without an option is returned.
 * 
 * @return Numeric value of the option.
 * @return 5 - when no option has been specified.
 */
int CCommandProcess::getOption() const
{
    initOpt();
    int i = 1;

    if(m_Vec.size() < 2)
    {
        return -1;
    }

    for(const auto& it : opts)
    {
        if(it.compare(m_Vec[1]) == 0)
        {
            return i;
        }

        i++;
    }

    return ++i;
}

/**
 * @brief Determine if the file is in a regular expression.
 * 
 * @param[in] expression Regular expression.
 * @param[in] str The file being compared.
 * 
 * @return true - when a match was found.
 * @return false - when match was not found.
 */
bool CCommandProcess::matchRegex(const string& expression, const string& str) const
{
    regex reg (expression);
    smatch match;

    if(regex_search(str, match, reg))
    {
        return true;
    }

    return false;
}

/**
 * @brief Calling a method to create a file.
 * 
 * See also sendCreateCom(), CCreate, getOption().
 * 
 */
void CCommandProcess::create() const
{   
    sendCreateCom(CCreate(), getOption());
}

/**
 * @brief Calling a method to copy a file.
 * 
 * See also sendFileCom(), CCopy, getOption().
 */
void CCommandProcess::copy() const
{
    sendFileCom(CCopy(), getOption());
}

/**
 * @brief Calling a method to move a file.
 * 
 * See also sendFileCom(), CMove, getOption().
 */
void CCommandProcess::move() const
{
    sendFileCom(CMove(), getOption());
}

/**
 * @brief Calling a method to delete a file.
 * 
 * See also sendDelCom(), CDelete, getOption().
 */
void CCommandProcess::del() const
{
    sendDelCom(CDelete(), getOption());
}

/**
 * @brief Calling a method to print contents of a file.
 * 
 * See also sendFileCom(), CPrint.
 */
void CCommandProcess::print() const
{
    sendFileCom(CPrint(), m_Vec[1]);
}

/**
 * @brief Calling a method to list a directory.
 * 
 * See also sendFileCom(), CList, getOption().
 */
void CCommandProcess::list() const
{
    sendFileCom(CList(), getOption() == 4 ? true : false);
}

/**
 * @brief Calling a method to change a working directory.
 * 
 * See also sendFileCom(), CChange.
 */
void CCommandProcess::change() const
{
    sendFileCom(CChange(), m_Vec[1]);
}

/**
 * @brief Calling a method to show disk information.
 * 
 * See also sendFileCom(), CMedia.
 */
void CCommandProcess::media() const
{
    sendFileCom(CMedia());
}

/**
 * @brief Calling a method to show help menu.
 * 
 * See also sendHelpCom(), CHelp.
 */
void CCommandProcess::help() const
{
    sendHelpCom(CHelp());
}

/**
 * @brief Calling a method to safely end program.
 * 
 * See also sendHelpCom(), CError.
 * 
 * @exception runtime_error - the user requests the end of the program.
 */
void CCommandProcess::end() const
{
    if(m_Vec.size() != 1)
    {
        sendHelpCom(CError());
        return;
    }

    throw runtime_error("exit");
}

/**
 * @brief Calling a method to display the directory where the user is located.
 * 
 * See also sendFileCom(), CCurrent.
 */
void CCommandProcess::current() const
{
    sendFileCom(CCurrent());
}

/**
 * @brief Calling a method for writing text to a file.
 * 
 * See also sendWriteCom(), CWrite.
 */
void CCommandProcess::write() const
{
    sendWriteCom(CWrite(), m_Vec[1], m_Vec[2]);
}

/**
 * @brief Sending a command to create a file.
 * 
 * Depending on the option obtained, the method for creating the required file is called.
 * If the condition of the number of command arguments is not met, an error message is displayed.
 * 
 * Se also CCreate::doCom(), sendHelpCom(), CError, CFile, CDir, CLink.
 * 
 * @param[in] c Specified command by user input.
 * @param[in] res Numeric value of the specified option.
 */
void CCommandProcess::sendCreateCom(const CCommand& c, int res) const
{
    if(res == 2) m_Vec.size() == 3 ? c.doCom(CFile(m_Vec[2])) : sendHelpCom(CError());
    if(res == 3) m_Vec.size() == 3 ? c.doCom(CDir(m_Vec[2])) : sendHelpCom(CError());
    if(res == 4) m_Vec.size() == 4 ? c.doCom(CLink(m_Vec[2], m_Vec[3])) : sendHelpCom(CError());
    if(res < 0 || res > 4) sendHelpCom(CError());
}

/**
 * @brief Obtaining the absolute path to the file.
 * 
 * The method gets the absolute path to the file.
 * If the file is in another directory, the files from the given directory will be loaded into the file vector.
 * 
 * See also CFileSystem, CFileSystem::loadFiles().
 * 
 * @param[in] file File path.
 * @param[in] cnt The number of calls to prevent reloading of files in the same directory.
 * 
 * @return File path.
 */
string CCommandProcess::getFile(const string& file, int cnt) const
{
    CFileSystem fs;
    string path = absolute(file);

    if(file.find("/") != string::npos && cnt == 0)
    {
        string name = file;
        auto toErasePos = file.find_last_of("/\\");
        string toErase = file.substr(toErasePos + 1);
        auto pos = name.find(toErase, toErasePos);
        auto len = toErase.length();
        name = name.erase(pos, len);
        fs.loadFiles(name);
    }

    return path;
}

/**
 * @brief Sending a command to copy or move a file(s).
 * 
 * Depending on the option obtained, either a regular expression is searched for files or a single file operation is performed.
 * An exception is thrown in the event of a shortage or excess of the necessary arguments to perform the operation.
 * 
 * See also CCopy::doCom(), CMove::doCom(), sendHelpCom(), matchRegex(), CFileSystem, CError, CException, CFileSystem::getVector(), getFile(), CFileType::getFileName().
 * 
 * @param[in] c Specified command by user input.
 * @param[in] res Numeric value of the specified option.
 * 
 * @exception CException - source file does not exist.
 */
void CCommandProcess::sendFileCom(const CCommand& c, int res) const
{
    CFileSystem fs;
    bool reg;
    bool found = false;

    if(res == -1 || (res == 1 && m_Vec.size() != 4) || (res == 5 && m_Vec.size() != 3) || (res != 1 && m_Vec.size() != 3))
    {
        sendHelpCom(CError());
        return;
    }

    if(res == 1)
    {
        reg = true;
    }
    else
    {
        reg = false;
    }

    if(reg)
    {
        int i = 0;

        for(const auto& it : fs.getVector()) 
        {
            string toFind = getFile(it->getFileName(), i++);

            if(matchRegex(m_Vec[2], toFind))
            {
                c.doCom(*it, m_Vec[3]);
                found = true;
            }
        }
    }
    else
    {
        string toFind = getFile(m_Vec[1], 0);

        for(const auto& it : fs.getVector())
        {
            if(it->getFileName().compare(toFind) == 0)
            {
                c.doCom(*it, m_Vec[2]);
                found = true;
                break;
            }
        }
    }

    if(!found)
    {
        throw CException(exTxt.DoesntExist);
    }
}

/**
 * @brief Sending a command to list directory contents.
 * 
 * Based on the obtained option, either a short listing of files in the directory or a long, more detailed listing of files in the directory is called.
 * 
 * See also sendHelpCom(), CList::doCom(), CError.
 * 
 * @param[in] c Specified command by user input.
 * @param[in] l Decision boolean value for a short or long listing.
 */
void CCommandProcess::sendFileCom(const CCommand& c, bool l) const
{
    if((m_Vec.size() != 1 && l == false) || (m_Vec.size() != 2 && l == true))
    {
        sendHelpCom(CError());
        return;
    }

    c.doCom(l);
}

/**
 * @brief Sending a command to do operations without arguments and options such as media, current and help.
 * 
 * See also sendHelpCom(), CMedia::doCom(), CCurrent::doCom(), CHelp::doCom(), CError.
 * 
 * @param[in] c Specified command by user input.
 */
void CCommandProcess::sendFileCom(const CCommand& c) const
{
    if(m_Vec.size() != 1)
    {
        sendHelpCom(CError());
        return;
    }

    c.doCom();
}

/**
 * @brief Sending a command to print contents of a regular file and to change directories.
 * 
 * See also sendHelpCom(), CPrint::doCom(), CChange::doCom(), CError.
 * 
 * @param[in] c Specified command by user input.
 * @param[in] src The specified path.
 */
void CCommandProcess::sendFileCom(const CCommand& c, const string& src) const
{
    if(m_Vec.size() != 2)
    {
        sendHelpCom(CError());
        return;
    }

    c.doCom(src);
}

/**
 * @brief Sending a command to delete file(s).
 * 
 * Based on the obtained option, it is decided whether to delete files according to the regular expression or whether to delete one file.
 * 
 * See also CDelete::doCom(), sendHelpCom(), matchRegex(), CFileSystem, CError, CException, CFileSystem::getVector(), getFile(), CFileType::getFileName().
 * 
 * @param[in] c Specified command by user input.
 * @param[in] res The specified file path.
 * 
 * @exception CException - source file does not exist.
 */
void CCommandProcess::sendDelCom(const CCommand& c, int res) const
{
    CFileSystem fs;
    bool reg;
    bool found = false;

    if(res == -1 || (res == 1 && m_Vec.size() != 3) || (res == 5 && m_Vec.size() != 2))
    {
        sendHelpCom(CError());
        return;
    }

    if(res == 1)
    {
        reg = true;
    }
    else
    {
        reg = false;
    }

    if(reg)
    {
        int i = 0;

        for(const auto& it : fs.getVector()) 
        {
            string toFind = getFile(it->getFileName(), i++);

            if(matchRegex(m_Vec[2], toFind))
            {
                c.doCom(*it);
                found = true;
            }
        }
    }
    else
    {
        string toFind = getFile(m_Vec[1], 0);

        for(const auto& it : fs.getVector())
        {
            if(it->getFileName().compare(toFind) == 0)
            {
                c.doCom(*it);
                found = true;
                break;
            }
        }
    }

    if(!found)
    {
        throw CException(exTxt.DoesntExist);
    }
}

/**
 * @brief Sending a command to show help menu.
 * 
 * See also CHelp::doCom().
 * 
 * @param[in] c Specified command by user input.
 */
void CCommandProcess::sendHelpCom(const CCommand& c) const
{
    c.doCom();
}

/**
 * @brief Sending a command to write text to the regular file.
 * 
 * See also sendHelpCom(), CWrite::doCom().
 * 
 * @param[in] c Specified command by user input.
 * @param[in] path File path.
 * @param[in] content Text to write to the file.
 */
void CCommandProcess::sendWriteCom(const CCommand& c, const string& path, const string& content) const
{
    if(m_Vec.size() != 3)
    {
        sendHelpCom(CError());
        return;
    }
    
    c.doCom(path, content);
}

/**
 * @brief Calling the processing of the requested order.
 * 
 * According to the passed numeric value, it is decided which method to call to process the requested command.
 * 
 * See also create(), copy(), move(), del(), print(), list(), change(), media(), help(), current(), write(). 
 * 
 * @param[in] i Numeric value of the command.
 */
void CCommandProcess::getCom(int i) const
{
    switch (i)
    {
    case 0:
            create();
        break;

    case 1:
            copy();
        break;

    case 2:
            move();
        break;

    case 3:
            del();
        break;

    case 4:
            print();
        break;

    case 5:
            list();
        break;

    case 6:
            change();
        break;

    case 7:
            media();
        break;

    case 8:
            help();
        break;

    case 9:
            end();
        break;

    case 10:
            current();
        break;

    case 11:
            write();
        break;
    
    default:
            help();
        break;
    }
}

/**
 * @brief The beginning of command processing.
 * 
 * According to the first word from the standard input, a match with the supported commands is sought.
 * In case of a match, the method for further processing is called.
 * In case of a discrepancy, an error message is displayed.
 * 
 * See also getCom(), sendHelpCom(), initCom(), CError.
 */
void CCommandProcess::processCommand()
{
    initCom();
    int i = 0;

    if(m_Vec.empty())
    {
        return;
    }

    transform(m_Vec[0].begin(), m_Vec[0].end(), m_Vec[0].begin(), [](unsigned char c)
    {
        return tolower(c);
    });

    for(const auto& it : vec)
    {
        if(it.compare(m_Vec[0]) == 0)
        {
            getCom(i);
            return;
        }

        i++;
    }

    sendFileCom(CError());
}

/**
 * @brief Method for obtaining arguments from standard input.
 * 
 * See also processCommand().
 * 
 * @param[in] vec Vector containing arguments from standard input.
 */
void CCommandProcess::passCommand(vector<string>& vec)
{
    m_Vec = vec;
    processCommand();
}