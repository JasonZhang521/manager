aux_source_directory(. connection_SRCS)

include_directories ("${PROJECT_SOURCE_DIR}/TraceLog"
"${PROJECT_SOURCE_DIR}/Common"
"${PROJECT_SOURCE_DIR}/Configure"
"${PROJECT_SOURCE_DIR}/EventHandler"
"${PROJECT_SOURCE_DIR}/PlatformWrapper"
)

add_library(connection  ${connection_SRCS})

target_link_libraries(connection
	                  configure
		              common
		             )

