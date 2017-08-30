#include "SshFtpSession.h"
#include "FilePathHandler.h"
#include "App.h"
#include "Trace.h"

#include <libssh/sftp.h>
#include <fstream>
#include <fcntl.h>

#include <time.h>
#include <QString>
#include <QDebug>
namespace SshWrapper
{

SshFtpSession::SshFtpSession(ssh_session session)
: session_(session)
, sftpSession_(sftp_new(session_))
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
    std::string remotePath = sftp_canonicalize_path (sftpSession_, remoteFile.c_str());

    TRACE_NOTICE("Download File " << remotePath << " to " << localDir);

    sftp_file file = sftp_open(sftpSession_, remotePath.c_str(), O_RDONLY, 0);
    if (file == NULL)
    {
        TRACE_WARNING("Error open remote file:" << remoteFile << ", error info:" << sftp_get_error(sftpSession_));
        return false;
    }

    // create a empty file in local
    const std::string FileName = FilePathHandler::getFileName(remotePath);
    const std::string FilePathTemp = localDir + "/" + FileName;
    const std::string FilePath = FilePathHandler::generateUniqueFileName(FilePathTemp);
    std::ofstream outfile(FilePath.c_str(), std::ofstream::binary);
    char buffer[MAX_XFER_BUF_SIZE];
    int nbytes = sftp_read(file, buffer, sizeof(buffer));
    while (nbytes > 0)
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

bool SshFtpSession::putFile(const std::string& localFile, const std::string& remoteDir)
{
    std::string remotePath = sftp_canonicalize_path (sftpSession_, remoteDir.c_str());
    TRACE_NOTICE("Upload File " << localFile << " to " << remotePath);
    std::ifstream infile(localFile.c_str(), std::ifstream::binary);
    // create a empty file in remote
    const std::string FileName = FilePathHandler::getFileName(localFile);
    std::string fileNameTemp = FileName;

    size_t index = 0;
    while (isRemoteFileExit(remotePath, fileNameTemp))
    {
        fileNameTemp = FilePathHandler::getIndexFileName(FileName, index);
        ++index;
    }
    const std::string FilePath = remotePath + "/" + fileNameTemp;

    sftp_file file = sftp_open(sftpSession_, FilePath.c_str(), O_CREAT | O_WRONLY, 0700);
    if (file == NULL)
    {
        TRACE_WARNING("Error create remote file:" << FilePath << ", error info:" << sftp_get_error(sftpSession_));
        return false;
    }

    char buffer[MAX_XFER_BUF_SIZE];
    std::streamsize nbytes = infile.readsome(buffer, sizeof(buffer));
    while (nbytes > 0)
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
    clock_t begin,end;
    double seconds;
    begin=clock();
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
		SftpDirAttribute dirAttribute;
		dirAttribute.name = attributes->name;
        dirAttribute.flags = attributes->flags;
        dirAttribute.type = attributes->type;
        dirAttribute.size = attributes->size;
        dirAttribute.uid = attributes->uid;
        dirAttribute.gid = attributes->gid;
        dirAttribute.owner = attributes->owner;
        dirAttribute.group = attributes->group;
        dirAttribute.permissions = attributes->permissions;
		dirAttributes.push_back(dirAttribute);
        sftp_attributes_free(attributes);
    }

    end=clock();
    seconds = (end - begin) / (double)CLOCKS_PER_SEC;
    qDebug()<<"@@"+QString::number(seconds);

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

}
