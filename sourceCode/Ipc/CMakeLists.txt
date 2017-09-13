aux_source_directory(. ipc_SRCS)

include_directories ("${PROJECT_SOURCE_DIR}/TraceLog"
"${PROJECT_SOURCE_DIR}/Common"
"${PROJECT_SOURCE_DIR}/Configure"
"${PROJECT_SOURCE_DIR}/Connection"
"${PROJECT_SOURCE_DIR}/Network"
"${PROJECT_SOURCE_DIR}/IpcMessage"
"${PROJECT_SOURCE_DIR}/Serialize"
"${PROJECT_SOURCE_DIR}/PlatformWrapper"
"${PROJECT_SOURCE_DIR}/Io"
"${PROJECT_SOURCE_DIR}/EventHandler"
"${PROJECT_SOURCE_DIR}/TimerHandler"
"${PROJECT_SOURCE_DIR}/Core"
)

add_library(ipc  ${ipc_SRCS})

target_link_libraries(ipc
	                  configure
		              common
		              network 
		              ipcmessage 
					  serialize
					  core
		             )

