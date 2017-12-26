aux_source_directory(. ProcessManagementSupport_SRCS)

include_directories ("${PROJECT_SOURCE_DIR}/TraceLog"
"${PROJECT_SOURCE_DIR}/Common"
"${PROJECT_SOURCE_DIR}/Configure"
"${PROJECT_SOURCE_DIR}/PlatformWrapper"
)

add_library(processmanagementsupport  ${ProcessManagementSupport_SRCS})

target_link_libraries(processmanagementsupport ${SSH_LIBs}
	                  configure
		              common
					  platformwrapper
		             )

