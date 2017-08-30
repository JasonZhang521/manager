#include "SftpDirAttribute.h"
#include <ostream>

namespace SshWrapper
{

SftpDirAttribute::SftpDirAttribute()
:flags(0)
,size(0)
,uid(0)
,gid(0)	
,permissions(0)
{}

SftpDirAttribute::SftpDirAttribute(const SftpDirAttribute& dirAttribute)
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

SftpDirAttribute& SftpDirAttribute::operator=(const SftpDirAttribute& dirAttribute)
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

bool SftpDirAttribute::operator==(const SftpDirAttribute& dirAttribute)
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

bool SftpDirAttribute::operator!=(const SftpDirAttribute& dirAttribute)
{
	return !(*this == dirAttribute);
}

std::ostream& operator<<(std::ostream& oStream, const SftpDirAttribute& b)
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
			<< ", permissions" << b.permissions
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
