aux_source_directory(. ipcmessage_SRCS)

include_directories ("${PROJECT_SOURCE_DIR}/TraceLog"
"${PROJECT_SOURCE_DIR}/Common"
"${PROJECT_SOURCE_DIR}/Configure"
"${PROJECT_SOURCE_DIR}/Connection"
"${PROJECT_SOURCE_DIR}/Network"
"${PROJECT_SOURCE_DIR}/Serialize"
"${PROJECT_SOURCE_DIR}/PlatformWrapper"
)

add_library(ipcmessage  ${ipcmessage_SRCS})

target_link_libraries(ipcmessage
	                  configure
		              common
		              network 
					  serialize
		             )

