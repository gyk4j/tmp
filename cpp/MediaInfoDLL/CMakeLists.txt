cmake_minimum_required(VERSION 3.10)
project(MediaInfoDLL
	VERSION 1.0
	DESCRIPTION "MediaInfoDLL"
	LANGUAGES CXX)

set(CMAKE_C_FLAGS "")
set(CMAKE_CXX_FLAGS "")

add_compile_definitions(-D_WIN32) # -DUNICODE -D_UNICODE

set(PROG "MediaInfoDLL.exe")
set(MY_CONSOLE 1)

if(MY_CONSOLE EQUAL 1)
    set(SUBSYSTEM "-mconsole")
else()
    set(SUBSYSTEM "-mwindows")
endif()

# set(MUNICODE "-municode")

set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${SUBSYSTEM} ${MUNICODE} -Os -s")

add_executable(${PROJECT_NAME}
	MediaInfoDLL.cpp MediaInfoDLL.h
)

target_link_libraries(${PROJECT_NAME})

