
set(CORE_SRCS
	GLoop.hpp
	System.hpp
	ThreadPool.hpp
)

add_subdirectory(ECM)

add_library(CORE_SRCS INTERFACE)
