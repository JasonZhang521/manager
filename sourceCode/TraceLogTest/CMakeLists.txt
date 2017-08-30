set(TraceLog_Unittest_SRCS
    TraceLog_unittest.cc
)
include_directories ("${PROJECT_SOURCE_DIR}/TraceLog"
"${PROJECT_SOURCE_DIR}/Common"
"${PROJECT_SOURCE_DIR}/Configure"
)
add_executable(TraceLog_unittest.elf ${TraceLog_Unittest_SRCS})
target_link_libraries (TraceLog_unittest.elf configure common ${TEST_LIBs})
