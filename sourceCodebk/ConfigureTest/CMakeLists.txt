set(Configure_Unittest_SRCS
    Configure_unittest.cc
)
include_directories ("${PROJECT_SOURCE_DIR}/Configure")
add_executable(Configure_unittest.elf ${Configure_Unittest_SRCS})
target_link_libraries (Configure_unittest.elf configure ${TEST_LIBs})
