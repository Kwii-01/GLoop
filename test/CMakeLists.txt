add_executable(${PROJECT_NAME} 
	main.cpp)

	target_include_directories(${PROJECT_NAME} PUBLIC ../src)
	target_include_directories(${PROJECT_NAME} PUBLIC ../src/tools)
	target_include_directories(${PROJECT_NAME} PUBLIC ../ecm)

