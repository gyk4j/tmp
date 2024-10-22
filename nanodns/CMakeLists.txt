cmake_minimum_required(VERSION 3.10)

project(nanodns)

add_executable(${CMAKE_PROJECT_NAME} nanodns.c)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    target_link_libraries(${CMAKE_PROJECT_NAME} ws2_32)
endif()