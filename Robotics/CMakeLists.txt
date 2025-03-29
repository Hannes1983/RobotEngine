cmake_minimum_required(VERSION 3.25)

project(RobotEngine VERSION 0.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
#Serial comm.---------------------------------------------
include_directories(third-party/include)

set(serial_SRCS third-party/src/serial.cc third-party/include/serial/serial.h 
    third-party/include/serial/v8stdint.h third-party/src/impl/list_ports/list_ports_win.cc)
list(APPEND serial_SRCS third-party/src/impl/win.cc)

add_library(serial ${serial_SRCS})
#target_link_libraries(serial rt)
#------------------------------------------------------------

#wxWidgets--------------------------------
set(wxWidgets_ROOT_DIR C:/wxWidgets)
set(wxWidgets_LIB_DIR ${wxWidgets_ROOT_DIR}/lib/vc_x64_lib )
message(${wxWidgets_ROOT_DIR})
message(${wxWidgets_LIB_DIR})
find_package(wxWidgets REQUIRED)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()
if (wxWidgets_FOUND)
  message("wxWidgets found!" ${wxWidgets_LIBRARIES} )
endif()
#----------------------------------------
#Source tree--------------
add_subdirectory(./Backend)
#--------------------------


#add_library(MainFrame GUI/Mainframe.cpp GUI/Mainframe.h)
add_executable(RobotEngine GUI/App.cpp GUI/App.h GUI/Mainframe.cpp GUI/Mainframe.h)

target_link_libraries(RobotEngine PUBLIC Backend)
target_link_libraries(RobotEngine PUBLIC serial)
target_link_libraries(RobotEngine PUBLIC ${wxWidgets_LIBRARIES})
#target_link_libraries(RobotEngine PUBLIC MainFrame)


target_include_directories(RobotEngine PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/Backend"
						  "${PROJECT_SOURCE_DIR}/GUI"
                          )