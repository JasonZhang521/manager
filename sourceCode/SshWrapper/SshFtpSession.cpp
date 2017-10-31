#include "SshFtpSession.h"
#include "FilePathHandler.h"
#include "App.h"
#include "Trace.h"

#include <libssh/sftp.h>
#include <fstream>
#include <fcntl.h>

namespace SshWrapper
{

SshFtpSession::SshFtpSession(ssh_session session)
: session_(session)
, sftpSession_(sftp_new(session_))
, stopGetFile_(false)
, stopPutFile_(false)
{
    if (session_ == NULL)
    {
        TRACE_WARNING("Session is NULL when initial sftp channel!");
        App::ExitNormal();
    }

    if (sftpSession_ == NULL)
    {
        TRACE_WARNING("sftpSession is NULL when initial sftp channel!");
        App::ExitNormal();
    }
}

SshFtpSession::~SshFtpSession()
{
    if (sftpSession_ != NULL)
    {
        sftp_free(sftpSession_);
    }
}

bool SshFtpSession::setup()
{
    int rc = sftp_init(sftpSession_);
    if (rc != SSH_OK)
    {
      TRACE_WARNING("Error init FTP: rc = " << rc << ", error info:" << sftp_get_error(sftpSession_));
      return false;
    }
    return true;
}

bool SshFtpSession::shutdown()
{
    return true;
}

bool SshFtpSession::getFile(const std::string& remoteFile, const std::string& localDir)
{
    TRACE_ENTER();
    // create a empty file in local
    const std::string FileName = FilePathHandler::getFileName(remoteFile);
    const std::string FilePath = localDir + "/" + FileName;
    const bool fromStartPos = true;
    return getFile(remoteFile, FilePath, fromStartPos);
}

bool SshFtpSession::getFileFromLastPos(const std::string& remoteFile, const std::string& localFile)
{
    TRACE_ENTER();
    const bool fromStartPos = false;
    return getFile(remoteFile, localFile, fromStartPos);
}

bool SshFtpSession::putFile(const std::string& localFile, const std::string& remoteDir)
{
    // when start upload file, set the stop flag false
    stopPutFile_ = false;

    std::string remotePath = sftp_canonicalize_path (sftpSession_, remoteDir.c_str());
    TRACE_NOTICE("Upload File " << localFile << " to " << remotePath);
    std::ifstream infile(localFile.c_str(), std::ifstream::binary);
    // create a empty file in remote
    const std::string FileName = FilePathHandler::getFileName(localFile);
    const std::string FilePath = remotePath + "/" + FileName;

    sftp_file file = sftp_open(sftpSession_, FilePath.c_str(), O_CREAT | O_WRONLY | O_TRUNC , 0700);
    if (file == NULL)
    {
        TRACE_WARNING("Error create remote file:" << FilePath << ", error info:" << sftp_get_error(sftpSession_));
        return false;
    }

    char buffer[MAX_XFER_BUF_SIZE];
    std::streamsize nbytes = infile.readsome(buffer, sizeof(buffer));
    while (nbytes > 0 && !stopPutFile_)
    {
        int nwritten = sftp_write(file, buffer, nbytes);
        if (nwritten != nbytes)
        {
            TRACE_WARNING("Error write remote file:" << FilePath << ", error info:" << sftp_get_error(sftpSession_));
            sftp_close(file);
            return false;
        }
        nbytes = infile.readsome(buffer, sizeof(buffer));
    }

    int rc = sftp_close(file);
    if (rc != SSH_OK)
    {
        TRACE_WARNING("Error close remote file:" << FilePath << ", error info:" << sftp_get_error(sftpSession_));
        return false;
    }

    return true;
}

bool SshFtpSession::listDir(const std::string& dirPath, SftpDirAttributes& dirAttributes)
{
    TRACE_ENTER();
    char * path = sftp_canonicalize_path (sftpSession_, dirPath.c_str());
    sftp_dir dir = sftp_opendir(sftpSession_, path);
    if (!dir)
	{
        TRACE_WARNING("Can not open Dir:" << dirPath  << ", error info:" << sftp_get_error(sftpSession_));
		return false;
    }
	sftp_attributes attributes = NULL;
    while ((attributes = sftp_readdir(sftpSession_, dir)) != NULL)
	{
        SftpFileAttribute fileAttribute;

        if (attributes->name != nullptr)
        {
            fileAttribute.name = attributes->name;
        }

        fileAttribute.flags = attributes->flags;
        fileAttribute.type = attributes->type;
        fileAttribute.size = attributes->size;
        fileAttribute.uid = attributes->uid;
        fileAttribute.gid = attributes->gid;

        if (attributes->owner != nullptr)
        {
            fileAttribute.owner = attributes->owner;
        }

        if (attributes->group)
        {
            fileAttribute.group = attributes->group;
        }
        fileAttribute.permissions = attributes->permissions;
        dirAttributes.push_back(fileAttribute);
        sftp_attributes_free(attributes);
    }

    if (!sftp_dir_eof(dir))
    {
        TRACE_WARNING("Can not list Dir:" << dirPath  << ", error info:" << sftp_get_error(sftpSession_));
        sftp_closedir(dir);
	    return false;
    }

    int rc = sftp_closedir(dir);
	if (rc != SSH_OK)
	{
        TRACE_WARNING("Can not close Dir:" << dirPath  << ", error code = " << rc << ", error info:" << sftp_get_error(sftpSession_));
        return false;
	}
    return true; 
}

void SshFtpSession::stopGetFile()
{
    stopGetFile_ = true;
}

void SshFtpSession::stopPutFile()
{
    stopPutFile_ = true;
}

bool SshFtpSession::listRemoteFileAttribute(const std::string& filePath, SftpFileAttribute& fileAttribute)
{
    TRACE_ENTER();
    char * path = sftp_canonicalize_path (sftpSession_, filePath.c_str());
    sftp_attributes attributes = sftp_stat(sftpSession_, path);
    if (attributes != nullptr)
    {
        if (attributes->name != nullptr)
        {
            fileAttribute.name = attributes->name;
        }

        fileAttribute.flags = attributes->flags;
        fileAttribute.type = attributes->type;
        fileAttribute.size = attributes->size;
        fileAttribute.uid = attributes->uid;
        fileAttribute.gid = attributes->gid;

        if (attributes->owner != nullptr)
        {
            fileAttribute.owner = attributes->owner;
        }

        if (attributes->group != nullptr)
        {
            fileAttribute.group = attributes->group;
        }

        fileAttribute.permissions = attributes->permissions;
        sftp_attributes_free(attributes);

    }
    else
    {
        TRACE_WARNING("Can not file information:" << path  << ", error info:" << sftp_get_error(sftpSession_));
        return false;
    }

    return true;
}

bool SshFtpSession::isRemoteFileExist(const std::string& remoteFile)
{
    TRACE_NOTICE("Check the file (" << remoteFile << ")'s existence");
    const std::string remotePath = sftp_canonicalize_path (sftpSession_, remoteFile.c_str());
    const std::string remoteDir = FilePathHandler::getFileDir(remotePath);
    const std::string remoteFileName = FilePathHandler::getFileName(remotePath);
    return isRemoteFileExit(remoteDir, remoteFileName);
}

bool SshFtpSession::renameRemoteFile(const std::string& srcFile, const std::string& dstFile)
{
    TRACE_NOTICE("Rename the file (" << srcFile << ") to (" << dstFile << ")");
    int rc = sftp_rename(sftpSession_, srcFile.c_str(), dstFile.c_str());
    if (rc < 0)
    {
        TRACE_WARNING("Can not renamethe file (" << srcFile << ") to (" << dstFile
                      << "), error code:" << rc << ", error info:" << sftp_get_error(sftpSession_));
        return false;
    }
    return true;
}

bool SshFtpSession::isRemoteFileExit(const std::string& remoteDir, const std::string& fileName)
{
    sftp_dir dir = sftp_opendir(sftpSession_, remoteDir.c_str());
    if (!dir)
    {
        TRACE_WARNING("Can not open Dir:" << remoteDir  << ", error info:" << sftp_get_error(sftpSession_));
        return true;
    }
    sftp_attributes attributes = NULL;
    while ((attributes = sftp_readdir(sftpSession_, dir)) != NULL)
    {
        if (std::string(attributes->name) == fileName)
        {
            std::cout << "The same" << std::endl;
            return true;
        }

        sftp_attributes_free(attributes);
    }

    int rc = sftp_closedir(dir);
    if (rc != SSH_OK)
    {
        TRACE_WARNING("Can not close Dir:" << remoteDir  << ", error code = " << rc << ", error info:" << sftp_get_error(sftpSession_));
    }

    return false;
}

bool SshFtpSession::getFile(const std::string& remoteFile, const std::string& localFile, bool fromStartPos)
{
    // when start download file, set the stop flag false
    stopGetFile_ = false;

    std::string remotePath = sftp_canonicalize_path (sftpSession_, remoteFile.c_str());

    TRACE_NOTICE("Download remote file " << remotePath << " to local file " << localFile);

    sftp_file file = sftp_open(sftpSession_, remotePath.c_str(), O_RDONLY, 0);
    if (file == NULL)
    {
        TRACE_WARNING("Error open remote file:" << remoteFile << ", error info:" << sftp_get_error(sftpSession_));
        return false;
    }

    std::ofstream::openmode mode = std::ofstream::binary;
    if (!fromStartPos)
    {
        mode = mode | std::ofstream::app;
    }
    std::ofstream outfile(localFile.c_str(), mode);
    if (!fromStartPos)
    {
        outfile.seekp(0, std::ofstream::end);
    }
    long pos = outfile.tellp();
    if (sftp_seek64(file, pos) < 0)
    {
       TRACE_WARNING("Can not seek the postion:" << pos << " for file " << remotePath);
       return false;
    }

    char buffer[MAX_XFER_BUF_SIZE];
    int nbytes = sftp_read(file, buffer, sizeof(buffer));
    while (nbytes > 0 && !stopGetFile_)
    {
        outfile.write(buffer, nbytes);
        nbytes = sftp_read(file, buffer, sizeof(buffer));
    }

    if (nbytes < 0)
    {
        TRACE_WARNING("Error read remote file:" << remotePath << ", error info:" << sftp_get_error(sftpSession_));
        sftp_close(file);
        return false;
    }

    int rc = sftp_close(file);
    if (rc != SSH_OK)
    {
        TRACE_WARNING("Error close the remote file:" << remotePath << ", error info:" << sftp_get_error(sftpSession_));
        return false;
    }

    return true;
}

}
