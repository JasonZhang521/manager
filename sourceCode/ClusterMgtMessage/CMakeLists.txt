aux_source_directory(. clustermgtmessage_SRCS)

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

add_library(clustermgtmessage  ${clustermgtmessage_SRCS})

target_link_libraries(clustermgtmessage
	                  configure
		              common
					  network
					  ipcmessage
					  environment
					  serialize
		             )

