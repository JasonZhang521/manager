aux_source_directory(. eventhandler_SRCS)

include_directories ("${PROJECT_SOURCE_DIR}/TraceLog"
"${PROJECT_SOURCE_DIR}/Common"
"${PROJECT_SOURCE_DIR}/Configure"
)

add_library(eventhandler  ${eventhandler_SRCS})

target_link_libraries(eventhandler ${SSH_LIBs}
	                  configure
		              common
		             )

