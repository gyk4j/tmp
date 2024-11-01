cmake_minimum_required(VERSION 3.10)
project(7zcl
	VERSION 1.0
	DESCRIPTION "Client7z"
	LANGUAGES CXX)

set(CMAKE_C_FLAGS "")
set(CMAKE_CXX_FLAGS "")

add_compile_definitions(-D_WIN32 -DUNICODE -D_UNICODE)

include(CMakePrintHelpers)

cmake_print_variables(CMAKE_FIND_ROOT_PATH)
cmake_print_variables(CMAKE_SYSROOT)

find_library(OLEAUT32_LIB NAMES oleaut32 HINTS "${CMAKE_PREFIX_PATH}" REQUIRED)
cmake_print_variables(OLEAUT32_LIB)
find_library(OLE32_LIB NAMES ole32 HINTS "${CMAKE_PREFIX_PATH}" REQUIRED)
cmake_print_variables(OLE32_LIB)
find_library(UUID_LIB NAMES uuid HINTS "${CMAKE_PREFIX_PATH}" REQUIRED)
cmake_print_variables(UUID_LIB)

set(PROG "7zcl.exe")
set(MY_CONSOLE 1)

if(MY_CONSOLE EQUAL 1)
    set(SUBSYSTEM "-mconsole")
else()
    set(SUBSYSTEM "-mwindows")
endif()

set(MUNICODE "-municode")

set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${SUBSYSTEM} ${MUNICODE} -Os -s")

add_executable(${PROJECT_NAME}
	CPP/7zip/UI/Client7z/Client7z.cpp
	CPP/Common/IntToString.cpp        CPP/Common/IntToString.h
	CPP/Common/NewHandler.cpp         CPP/Common/NewHandler.h
	CPP/Common/MyString.cpp           CPP/Common/MyString.h
	CPP/Common/StringConvert.cpp      CPP/Common/StringConvert.h
	CPP/Common/StringToInt.cpp        CPP/Common/StringToInt.h
	CPP/Common/MyVector.cpp           CPP/Common/MyVector.h
	CPP/Common/Wildcard.cpp           CPP/Common/Wildcard.h
	CPP/Windows/DLL.cpp               CPP/Windows/DLL.h
	CPP/Windows/FileDir.cpp           CPP/Windows/FileDir.h
	CPP/Windows/FileFind.cpp          CPP/Windows/FileFind.h
	CPP/Windows/FileIO.cpp            CPP/Windows/FileIO.h
	CPP/Windows/FileName.cpp          CPP/Windows/FileName.h
	CPP/Windows/PropVariant.cpp       CPP/Windows/PropVariant.h
	CPP/Windows/PropVariantConv.cpp   CPP/Windows/PropVariantConv.h
	CPP/7zip/Common/FileStreams.cpp   CPP/7zip/Common/FileStreams.h
)

target_link_libraries(${PROJECT_NAME} ${OLEAUT32_LIB} ${OLE32_LIB} ${UUID_LIB})

