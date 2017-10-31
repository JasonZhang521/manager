#include "SftpDirAttribute.h"
#include <ostream>

namespace SshWrapper
{

SftpFileAttribute::SftpFileAttribute()
:flags(0)
,size(0)
,uid(0)
,gid(0)	
,permissions(0)
{}

SftpFileAttribute::SftpFileAttribute(const SftpFileAttribute& dirAttribute)
:name(dirAttribute.name)
,flags(dirAttribute.flags)
,type(dirAttribute.type)
,size(dirAttribute.size)
,uid(dirAttribute.uid)
,gid(dirAttribute.gid)
,owner(dirAttribute.owner)
,group(dirAttribute.group)
,permissions(dirAttribute.permissions)
{}

SftpFileAttribute& SftpFileAttribute::operator=(const SftpFileAttribute& dirAttribute)
{
	name = dirAttribute.name;
	flags = dirAttribute.flags;
	type = dirAttribute.type;
	size = dirAttribute.size;
	uid = dirAttribute.uid;
	gid = dirAttribute.gid;
	owner = dirAttribute.owner;
	group = dirAttribute.group;
	permissions = dirAttribute.permissions;

	return *this;
}

bool SftpFileAttribute::operator==(const SftpFileAttribute& dirAttribute)
{
	if (this == &dirAttribute)
	{
		return true;
	}
	else
	{
		return (name == dirAttribute.name && 
		        flags == dirAttribute.flags && 
		        type == dirAttribute.type && 
		        size == dirAttribute.size && 
		        uid == dirAttribute.uid && 
		        gid == dirAttribute.gid && 
		        owner == dirAttribute.owner && 
		        group == dirAttribute.group && 
		        permissions == dirAttribute.permissions); 
	}
}

bool SftpFileAttribute::operator!=(const SftpFileAttribute& dirAttribute)
{
	return !(*this == dirAttribute);
}

std::ostream& operator<<(std::ostream& oStream, const SftpFileAttribute& b)
{
	oStream << "["
		    << "name=" << b.name
			<< ", flags=" << b.flags
			<< ", type=" << static_cast<int>(b.type)
			<< ", size=" << b.size
			<< ", uid=" << b.uid
			<< ", gid=" << b.gid
			<< ", owner=" << b.owner
			<< ", group=" << b.group
			<< ", permissions=" << b.permissions
			<< "]";

	return oStream;
}


std::ostream& operator<<(std::ostream& oStream, const SftpDirAttributes& bs)
{
	for (SftpDirAttributes::const_iterator it = bs.begin(); it != bs.end(); ++it)
	{
		oStream << (*it) << std::endl;
    }
	return oStream;
}

}
