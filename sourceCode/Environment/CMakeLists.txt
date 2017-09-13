aux_source_directory(. environment_SRCS)

include_directories ("${PROJECT_SOURCE_DIR}/TraceLog"
"${PROJECT_SOURCE_DIR}/Common"
"${PROJECT_SOURCE_DIR}/Configure"
"${PROJECT_SOURCE_DIR}/Serialize"
"${PROJECT_SOURCE_DIR}/PlatformWrapper"
"${PROJECT_SOURCE_DIR}/Network"
"${PROJECT_SOURCE_DIR}/TimerHandler"
"${PROJECT_SOURCE_DIR}/Io"
"${PROJECT_SOURCE_DIR}/Core"
"${PROJECT_SOURCE_DIR}/Network"
)

add_library(environment  ${environment_SRCS})

target_link_libraries(environment
	                  configure
		              common
					  serialize
					  platformwrapper
					  network
					  timerhandler
					  io
					  core
					  network
		             )

