aux_source_directory(. serialize_SRCS)

include_directories ("${PROJECT_SOURCE_DIR}/TraceLog"
"${PROJECT_SOURCE_DIR}/Common"
"${PROJECT_SOURCE_DIR}/Configure"
"${PROJECT_SOURCE_DIR}/PlatformWrapper"
)

add_library(serialize  ${serialize_SRCS})

target_link_libraries(serialize
	              configure
		      common
		     )

