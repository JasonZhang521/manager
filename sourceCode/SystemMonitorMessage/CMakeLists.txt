aux_source_directory(. systemmonitormessage_SRCS)

include_directories ("${PROJECT_SOURCE_DIR}/TraceLog"
"${PROJECT_SOURCE_DIR}/Common"
"${PROJECT_SOURCE_DIR}/Configure"
"${PROJECT_SOURCE_DIR}/Connection"
"${PROJECT_SOURCE_DIR}/Network"
"${PROJECT_SOURCE_DIR}/IpcMessage"
"${PROJECT_SOURCE_DIR}/Environment"
"${PROJECT_SOURCE_DIR}/Serialize"
"${PROJECT_SOURCE_DIR}/PlatformWrapper"
)

add_library(systemmonitormessage  ${systemmonitormessage_SRCS})

target_link_libraries(systemmonitormessage
	                  configure
		              common
					  network
					  ipcmessage
					  environment
					  serialize
		             )

