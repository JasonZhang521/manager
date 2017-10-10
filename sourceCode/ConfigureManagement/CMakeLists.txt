aux_source_directory(. configuremanagement_SRCS)

include_directories ("${PROJECT_SOURCE_DIR}/TraceLog"
"${PROJECT_SOURCE_DIR}/Common"
"${PROJECT_SOURCE_DIR}/Configure"
"${PROJECT_SOURCE_DIR}/Serialize"
"${PROJECT_SOURCE_DIR}/Network"
"${PROJECT_SOURCE_DIR}/PlatformWrapper"
"${PROJECT_SOURCE_DIR}/TimerHandler"
"${PROJECT_SOURCE_DIR}/Io"
"${PROJECT_SOURCE_DIR}/Core"
)

add_library(configuremanagement  ${configuremanagement_SRCS})

target_link_libraries(configuremanagement ${SSH_LIBs}
	                  configure
					  serialize
		              common
					  network
		             )

