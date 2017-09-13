set(LIBs pthread)
set(SSH_LIBs ssh ssh_threads)	
set(TEST_LIBs ${LIBs} gtest gmock gtest_main gmock_main)
cmake_minimum_required (VERSION 2.6)

add_subdirectory(Configure)
add_subdirectory(Common)
add_subdirectory(SshWrapper)
add_subdirectory(libssh_demo)

#Unit test
add_subdirectory(ConfigureTest)
add_subdirectory(TraceLogTest)
add_subdirectory(SshWrapperTest)
