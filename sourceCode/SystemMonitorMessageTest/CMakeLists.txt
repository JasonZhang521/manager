aux_source_directory(. SystemMonitorMessage_Unittest_SRCS)
include_directories ("${PROJECT_SOURCE_DIR}/SystemMonitorMessage"
"${PROJECT_SOURCE_DIR}/Common"
"${PROJECT_SOURCE_DIR}/Configure"
"${PROJECT_SOURCE_DIR}/SystemMonitorMessage"
"${PROJECT_SOURCE_DIR}/IpcMessage"
"${PROJECT_SOURCE_DIR}/Network"
"${PROJECT_SOURCE_DIR}/Serialize"
"${PROJECT_SOURCE_DIR}/PlatformWrapper"
"${PROJECT_SOURCE_DIR}/Environment"
)
add_executable(SystemMonitorMessage_unittest.elf ${SystemMonitorMessage_Unittest_SRCS})
target_link_libraries (SystemMonitorMessage_unittest.elf
		               configure
					   common
					   serialize
					   systemmonitormessage
					   ipcmessage
					   ${TEST_LIBs})
