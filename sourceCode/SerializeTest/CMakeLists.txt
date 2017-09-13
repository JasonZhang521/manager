aux_source_directory(. Serialize_Unittest_SRCS)
include_directories ("${PROJECT_SOURCE_DIR}/Serialize"
"${PROJECT_SOURCE_DIR}/Common"
"${PROJECT_SOURCE_DIR}/Configure"
"${PROJECT_SOURCE_DIR}/PlatformWrapper"
)
add_executable(Serialize_unittest.elf ${Serialize_Unittest_SRCS})
target_link_libraries (Serialize_unittest.elf configure platformwrapper common serialize ${TEST_LIBs})
