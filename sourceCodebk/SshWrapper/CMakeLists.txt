set(sshwrapper_SRCS
    SshClientSession.cpp
    SshShellChannel.cpp
	SshInteractiveShellChannel.cpp
	SshFtpSession.cpp
    SshClient.cpp
	SftpDirAttribute.cpp
)
include_directories ("${PROJECT_SOURCE_DIR}/TraceLog"
"${PROJECT_SOURCE_DIR}/Common"
"${PROJECT_SOURCE_DIR}/Configure"
)
add_library(sshwrapper  ${sshwrapper_SRCS})
target_link_libraries(sshwrapper ${SSH_LIBs}
	              configure
		      common
		     )

