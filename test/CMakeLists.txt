add_executable(${PROJECT_NAME} 
	main.cpp)

target_link_libraries(${PROJECT_NAME} CORE_SRCS)

set_target_properties(${PROJECT_NAME} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY})