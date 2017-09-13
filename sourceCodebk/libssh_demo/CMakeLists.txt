set(libssh_demo_SRCS
    SshClient.cpp
	TestMain.cpp
)
include_directories ("${PROJECT_SOURCE_DIR}/TraceLog"
"${PROJECT_SOURCE_DIR}/Common"
"${PROJECT_SOURCE_DIR}/Configure"
)
add_executable(libssh_demo.elf ${libssh_demo_SRCS})
target_link_libraries (libssh_demo.elf ${SSH_LIBs}
		configure
		common
		)
