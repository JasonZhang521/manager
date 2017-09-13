#ifndef _ENVIRONMENT_SHELLCOMMANDDFOUTPUT_H_
#define _ENVIRONMENT_SHELLCOMMANDDFOUTPUT_H_
#include <stdint.h>
#include <vector>
#include <string>
#include <iostream>

namespace Serialize {
class WriteBuffer;
class ReadBuffer;
}

/* *** df output
 *
Filesystem        1K-blocks      Used Available Use% Mounted on
/dev/sda2             57591044  20032372  34633156  37% /
tmpfs                  1019896       276   1019620   1% /dev/shm
/dev/sda1               297485     30366    251759  11% /boot
/dev/sr0               3351190   3351190         0 100% /media/RHEL_6.0 x86_64 Disc 1
*/
namespace Environment {
class ShellCommandDfOutput
{
    std::string fileSystem_;
    uint64_t oneKBlock_ = 0;
    uint64_t used_ = 0;
    uint64_t available_ = 0;
    uint8_t pecentageUsed_ = 0;
    std::string mountedOn_;
public:
    ShellCommandDfOutput();
    ShellCommandDfOutput(const ShellCommandDfOutput& output);
    ShellCommandDfOutput& operator =(const ShellCommandDfOutput& output);
    inline const std::string& getFileSystem() const {return fileSystem_;}
    inline void setFileSystem(const std::string& fileSystem) {fileSystem_ = fileSystem;}
    inline uint64_t getOneKBlock() const {return oneKBlock_;}
    inline void setOneKBlock(uint64_t oneKBlock) {oneKBlock_ = oneKBlock;}
    inline uint64_t getUsed() const {return used_;}
    inline void setUsed(uint64_t used) {used_ = used;}
    inline uint64_t getAvailable() const {return available_;}
    inline void setAvailable(uint64_t available) {available_ = available;}
    inline uint8_t getPecentageUsed() const {return pecentageUsed_;}
    inline void setPecentageUsed(uint8_t pecentageUsed) {pecentageUsed_ = pecentageUsed;}
    inline const std::string& getMountedOn() const {return mountedOn_;}
    inline void setMountedOn(const std::string& mountedOn) {mountedOn_ = mountedOn;}

    void serialize(Serialize::WriteBuffer& writeBuffer) const;
    void unserialize(Serialize::ReadBuffer& readBuffer);
    std::ostream& operator <<(std::ostream& os) const;
    bool operator ==(const ShellCommandDfOutput& output) const;
};

using ShellCommandDfOutputs = std::vector<ShellCommandDfOutput>;
}

inline std::ostream& operator <<(std::ostream& os, const Environment::ShellCommandDfOutput& output)
{
    return output.operator <<(os);
}

#endif // _ENVIRONMENT_SHELLCOMMANDDFOUTPUT_H_
