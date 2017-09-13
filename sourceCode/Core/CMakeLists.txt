aux_source_directory(. core_SRCS)

include_directories ("${PROJECT_SOURCE_DIR}/TraceLog"
"${PROJECT_SOURCE_DIR}/Common"
"${PROJECT_SOURCE_DIR}/Configure"
"${PROJECT_SOURCE_DIR}/EventHandler"
"${PROJECT_SOURCE_DIR}/TimerHandler"
"${PROJECT_SOURCE_DIR}/PlatformWrapper"
"${PROJECT_SOURCE_DIR}/Io"
)

add_library(core  ${core_SRCS})

target_link_libraries(core
	                  configure
		              common
					  eventhandler
					  timerhandler
					  platformwrapper
					  io
		             )

