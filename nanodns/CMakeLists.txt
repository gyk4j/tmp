cmake_minimum_required(VERSION 3.10)

project(nanodns)

add_executable(nanodns nanodns.c)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    target_link_libraries(nanodns wsock32 ws2_32)
endif()