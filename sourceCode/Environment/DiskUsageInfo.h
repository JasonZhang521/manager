#ifndef _ENVIRONMENT_DISKUSAGEINFO_H_
#define _ENVIRONMENT_DISKUSAGEINFO_H_
#include "ShellCommandDataType.h"
#include "ShellCommandDfOutput.h"
#include "Component.h"
#include "Macro.h"

namespace Serialize {
class WriteBuffer;
class ReadBuffer;
}

namespace Environment {
class DiskUsageInfo
{
    ShellCommandDfOutput rootDirUsage_;
    ShellCommandDfOutput bootInitDirUsage_;
    ShellCommandDfOutput dfHomeDirUsage_;
    uint64_t homeDirUsage_;
public:
    DiskUsageInfo();
    void serialize(Serialize::WriteBuffer& writeBuffer) const;
    void unserialize(Serialize::ReadBuffer& readBuffer);
    std::ostream& operator <<(std::ostream& os) const;
    bool operator ==(const DiskUsageInfo& info) const;
    const ShellCommandDfOutput& getRootDirUsage() const;
	void setRootDirUsage(const ShellCommandDfOutput& output);
    const ShellCommandDfOutput& getBootInitDirUsage() const;
	void setBootInitDirUsage(const ShellCommandDfOutput& output);
    const ShellCommandDfOutput& getDfHomeDirUsage() const;
    void setDfHomeDirUsage(const ShellCommandDfOutput& output);
    uint64_t getHomeDirUsage() const;
    void setHomeDirUsage(uint64_t usage);

    void update();

private:
    void updateDfCommandDirUsage();
    void updateHomeDirUsage();
public:
     GETCLASSNAME(NetworkInfo)
};
}

inline std::ostream& operator <<(std::ostream& os, const Environment::DiskUsageInfo& info)
{
    return info.operator <<(os);
}

#endif // DISKUSAGEINFO_H
