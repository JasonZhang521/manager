set(SSH_LIBs ssh ssh_threads)	
set(SshOneTimeShellCmdMainTest_SRCS
    SshOneTimeShellCmdMainTest.cpp
)
set(SshInteractiveShellCmdMainTest_SRCS
    SshInteractiveShellCmdMainTest.cpp
)
set(SshSftpShellCmdMainTest_SRCS
    SshSftpShellCmdMainTest.cpp
)
include_directories ("${PROJECT_SOURCE_DIR}/TraceLog"
"${PROJECT_SOURCE_DIR}/Common"
"${PROJECT_SOURCE_DIR}/Configure"
"${PROJECT_SOURCE_DIR}/SshWrapper"
)
add_executable(SshOneTimeShellCmdMainTest.elf ${SshOneTimeShellCmdMainTest_SRCS})
add_executable(SshInteractiveShellCmdMainTest.elf ${SshInteractiveShellCmdMainTest_SRCS})
add_executable(SshSftpShellCmdMainTest.elf ${SshSftpShellCmdMainTest_SRCS})
target_link_libraries (SshOneTimeShellCmdMainTest.elf ${SSH_LIBs}
		configure
		common
		sshwrapper
		)
target_link_libraries (SshInteractiveShellCmdMainTest.elf ${SSH_LIBs}
		configure
		common
		sshwrapper
		)
target_link_libraries (SshSftpShellCmdMainTest.elf ${SSH_LIBs}
		configure
		common
		sshwrapper
		)
