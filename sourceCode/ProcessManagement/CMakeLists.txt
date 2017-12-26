aux_source_directory(. ProcessManagement_SRCS)
include_directories ("${PROJECT_SOURCE_DIR}/Common"
                     "${PROJECT_SOURCE_DIR}/Configure"
                     "${PROJECT_SOURCE_DIR}/Io"
		     "${PROJECT_SOURCE_DIR}/PlatformWrapper"
                     "${PROJECT_SOURCE_DIR}/Core"
                     "${PROJECT_SOURCE_DIR}/EventHandler"
                     "${PROJECT_SOURCE_DIR}/TimerHandler"
                     "${PROJECT_SOURCE_DIR}/TraceLog"
                     "${PROJECT_SOURCE_DIR}/ProcessManagementSupport"
																										 
)
add_executable(ProcessManagement.elf ${ProcessManagement_SRCS})
target_link_libraries (ProcessManagement.elf
		               configure
					   common
					   io
					   platformwrapper
					   core
					   eventhandler
					   timerhandler
                                           processmanagementsupport
					   ${LIBs}
					  )
