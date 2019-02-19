if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	message(FATAL_ERROR "Prevented in-tree built. Please create a builddirectory outside of the source code and call cmake from there")
endif ()

cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -g3 -std=c++17")
set(CXX_STANDARD 17)

project(Game VERSION 1.0)

add_subdirectory(src)
add_subdirectory(test)

target_link_libraries(${PROJECT_NAME} CORE_SRCS ${CMAKE_DL_LIBS})

set_target_properties(${PROJECT_NAME} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY})
