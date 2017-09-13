aux_source_directory(. io_SRCS)

include_directories ("${PROJECT_SOURCE_DIR}/TraceLog"
"${PROJECT_SOURCE_DIR}/Common"
"${PROJECT_SOURCE_DIR}/Configure"
"${PROJECT_SOURCE_DIR}/EventHandler"
"${PROJECT_SOURCE_DIR}/PlatformWrapper"
)

add_library(io  ${io_SRCS})

target_link_libraries(io
	                  configure
		              common
		             )

