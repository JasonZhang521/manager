aux_source_directory(. Network_Unittest_SRCS)
include_directories ("${PROJECT_SOURCE_DIR}/Network"
"${PROJECT_SOURCE_DIR}/Common"
"${PROJECT_SOURCE_DIR}/Configure"
"${PROJECT_SOURCE_DIR}/Serialize"
"${PROJECT_SOURCE_DIR}/PlatformWrapper"
)
add_executable(Network_unittest.elf ${Network_Unittest_SRCS})
target_link_libraries (Network_unittest.elf configure common network serialize ${TEST_LIBs})
