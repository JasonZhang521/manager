aux_source_directory(. Environment_Unittest_SRCS)
include_directories ("${PROJECT_SOURCE_DIR}/Environment"
"${PROJECT_SOURCE_DIR}/Common"
"${PROJECT_SOURCE_DIR}/Configure"
"${PROJECT_SOURCE_DIR}/Serialize"
"${PROJECT_SOURCE_DIR}/Network"
"${PROJECT_SOURCE_DIR}/TimerHandler"
"${PROJECT_SOURCE_DIR}/PlatformWrapper"
"${PROJECT_SOURCE_DIR}/Core"
"${PROJECT_SOURCE_DIR}/Io"
)
add_executable(Environment_unittest.elf ${Environment_Unittest_SRCS})
target_link_libraries (Environment_unittest.elf
		configure
		common
		environment
		serialize
		network
	    platformwrapper	
		${TEST_LIBs})
