aux_source_directory(. ClusterNodesControl_SRCS)
include_directories ("${PROJECT_SOURCE_DIR}/Environment"
                     "${PROJECT_SOURCE_DIR}/Common"
                     "${PROJECT_SOURCE_DIR}/Configure"
                     "${PROJECT_SOURCE_DIR}/Ipc"
                     "${PROJECT_SOURCE_DIR}/IpcMessage"
                     "${PROJECT_SOURCE_DIR}/Network"
                     "${PROJECT_SOURCE_DIR}/Io"
					 "${PROJECT_SOURCE_DIR}/PlatformWrapper"
                     "${PROJECT_SOURCE_DIR}/Core"
                     "${PROJECT_SOURCE_DIR}/SystemMonitorMessage"
                     "${PROJECT_SOURCE_DIR}/EventHandler"
                     "${PROJECT_SOURCE_DIR}/TimerHandler"
                     "${PROJECT_SOURCE_DIR}/TraceLog"
                     "${PROJECT_SOURCE_DIR}/Serialize"
																										 
)
add_executable(ClusterNodesControl.elf ${ClusterNodesControl_SRCS})
target_link_libraries (ClusterNodesControl.elf
		               configure
					   common
					   environment
					   ipc
					   ipcmessage
					   network
					   io
					   platformwrapper
					   core
					   systemmonitormessage
					   eventhandler
					   timerhandler
					   serialize
					   ${LIBs}
					  )
