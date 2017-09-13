aux_source_directory(. network_SRCS)

include_directories ("${PROJECT_SOURCE_DIR}/TraceLog"
"${PROJECT_SOURCE_DIR}/Common"
"${PROJECT_SOURCE_DIR}/Configure"
"${PROJECT_SOURCE_DIR}/EventHandler"
"${PROJECT_SOURCE_DIR}/TimerHandler"
"${PROJECT_SOURCE_DIR}/Serialize"
"${PROJECT_SOURCE_DIR}/Io"
"${PROJECT_SOURCE_DIR}/PlatformWrapper"
"${PROJECT_SOURCE_DIR}/Core"
)

add_library(network  ${network_SRCS})

target_link_libraries(network ${SSH_LIBs}
	                  configure
					  eventhandler
					  serialize
		              common
					  io
					  platformwrapper
		             )

