#ifndef _SSHWRAPPER_SFTPDIRATTRIBUTE_H_
#define _SSHWRAPPER_SFTPDIRATTRIBUTE_H_
#include <vector>
#include <string>
#include <stdint.h>

namespace SshWrapper
{

struct SftpDirAttribute
{
	SftpDirAttribute();
	SftpDirAttribute(const SftpDirAttribute& dirAttribute);
	SftpDirAttribute& operator=(const SftpDirAttribute& dirAttribute);
	bool operator==(const SftpDirAttribute& dirAttribute);
	bool operator!=(const SftpDirAttribute& dirAttribute);
	std::string name;
    uint32_t flags;
    uint8_t type;
    uint64_t size;
    uint32_t uid;
    uint32_t gid;
	std::string owner; /* set if openssh and version 4 */
	std::string group; /* set if openssh and version 4 */
    uint32_t permissions;
};

typedef std::vector<SftpDirAttribute> SftpDirAttributes;

std::ostream& operator<<(std::ostream& oStream, const SftpDirAttribute& b);
std::ostream& operator<<(std::ostream& oStream, const SftpDirAttributes& bs);

}
#endif
